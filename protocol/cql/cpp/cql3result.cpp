/*
   Copyright (C) 2013 Nipun Talukdar

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include <cql3result.hpp>
#include <utility.hpp>
#include <iostream>

using namespace GeetCass;
using std::endl;
using std::cout;

void Cql3RowMetaData::init(ByteBuffer& buffer, Cql3RowMetaData& metadata)
{
    metadata._flags = buffer.getUInt32();
    metadata._column_count = buffer.getUInt32();
    if (GLOBAL_TABLE_SPEC_PRESENT == metadata._flags) {
        Utility::readShortString(buffer, metadata._global_table_spec[0]);
        Utility::readShortString(buffer, metadata._global_table_spec[1]);
    }
    string col ;
    uint32_t i = 0;
    while (i++< metadata._column_count){
        Utility::readShortString(buffer, col);
        metadata._columns.push_back(new Column(col, (Cql3Types) buffer.getUInt16()));
    }
    metadata._row_count = buffer.getUInt32();

}

Column* Cql3RowMetaData::getColumn(size_t index) const throw (char *)
{
    if (index >= _columns.size())
        throw "out of bound";
  
    return _columns[index];
     
}

Cql3RowMetaData::~Cql3RowMetaData()
{
    vector <Column *>::iterator it = _columns.begin();
    while (it != _columns.end()) {
        delete *it;
        ++it;
    }
    _columns.clear();
}


// Code for cql3 rows

void Cql3Rows::init(ByteBuffer& buffer, Cql3Rows& rows, size_t max_pos)
{
    rows._buffer = &buffer;
    rows._metaData.init(buffer, rows._metaData);
    rows._startInByteBuffer = buffer.currentPosition();
    if (max_pos >= buffer.capacity())
        max_pos = buffer.capacity() - 1;
    rows._stopInByteBuffer = max_pos;
    rows._currentRow = 0;
}

uint32_t  Cql3Rows::getRowCount() const
{
    return _metaData.getRowCount();
}

Cql3Row::Cql3Row(void *buffer, size_t size, unordered_map<Column *, size_t, 
        ColumnHash, ColumnEq>* positions)
{
    _row_size = size;
    _data = buffer;
    _buffer = new ByteBuffer(size, ByteBuffer::Endian::BIG, buffer, size);
    _columnPositions = positions;
}

Cql3Row::~Cql3Row() 
{
    delete _buffer;
    delete _columnPositions;
}

bool Cql3Row::getBoolean(const string& column, bool& out)
{
    Column dummy(column, Cql3Types::INT);
    std::unordered_map<Column*, size_t, ColumnHash, ColumnEq >::iterator it =
        _columnPositions->find(&dummy);
    if (it == _columnPositions->end() || 
            it->first->getColumnType() != Cql3Types::BOOLEAN)
        return false;
    try {
        _buffer->position(it->second + 4);
        uint8_t val = _buffer->getUInt8();
        if (val == 1)
            out = true;
        else
            out = false;
        return true;
    }catch (ByteBufferException& e){
        return false;
    }
}   

bool Cql3Row::getAscii(const string& column, string& out)
{
    Column dummy(column, Cql3Types::INT);
    std::unordered_map<Column*, size_t, ColumnHash, ColumnEq >::iterator it =
        _columnPositions->find(&dummy);
    if (it == _columnPositions->end() || 
            it->first->getColumnType() != Cql3Types::ASCII)
        return false;
    try {
       _buffer->position(it->second);
       Utility::readLongString(*_buffer, out);
       return true;
    }catch (ByteBufferException& e){
        return false;
    }
}   

bool Cql3Row::getString(const string& column, string& out)
{
    Column dummy(column, Cql3Types::INT);
    std::unordered_map<Column*, size_t, ColumnHash, ColumnEq >::iterator it =
        _columnPositions->find(&dummy);
    if (it == _columnPositions->end() || 
            it->first->getColumnType() != Cql3Types::VARCHAR)
        return false;
    try {
       _buffer->position(it->second);
       Utility::readLongString(*_buffer, out);
       return true;
    }catch (ByteBufferException& e){
        return false;
    }
}   

bool Cql3Row::getInt(const string& column, int32_t& out)
{
    Column dummy(column, Cql3Types::INT);
    std::unordered_map<Column*, size_t, ColumnHash, ColumnEq >::iterator it =
        _columnPositions->find(&dummy);
    if (it == _columnPositions->end() || 
            it->first->getColumnType() != Cql3Types::INT)
        return false;
    try {
       // first  4 bytes are for size of integerers
       _buffer->position(it->second + 4);
       out = _buffer->getInt32();
       return true;
    }catch (ByteBufferException& e){
        return false;
    }
}   

Cql3Row* Cql3Rows::getNextRow()
{
    size_t position = _buffer->currentPosition();
    uint32_t colc = _metaData.getColumnCount();
    uint32_t i = 0;
    size_t size = 0;
    if (_currentRow >= _metaData.getRowCount())
        return 0;
    unordered_map<Column *, size_t, ColumnHash, ColumnEq>* relativePositions
        = new unordered_map<Column*, size_t, ColumnHash, ColumnEq>();
    while (i < colc) {
        Column *column = _metaData.getColumn(i);
        (*relativePositions)[column] = _buffer->currentPosition() - position;
        if (column->column_type == Cql3Types::VARCHAR) {
            size = _buffer->getUInt32();
            _buffer->proceed(size);
        } else if (column->column_type == Cql3Types::INT) {
            _buffer->proceed(sizeof(int32_t) + 4);
        } else if (column->column_type == Cql3Types::ASCII) {
            size = _buffer->getUInt32();
            _buffer->proceed(size);
        } else if (column->column_type == Cql3Types::DECIMAL) {
            size = _buffer->getUInt32();
            _buffer->proceed(size);
        } else if (column->column_type == Cql3Types::BOOLEAN) {
            // 5 = 4+1  , 4 for size of the boolean value, 1 for boolean value
            _buffer->proceed(5);
        }
        i++;
    }
    _currentRow++;
    return new Cql3Row((char *) _buffer->getRaw() + position, _buffer->currentPosition()
            - position, relativePositions);

}


Cql3Result::Cql3Result(ByteBuffer& buffer)
{
    _resultData = &buffer;
    _resultCode = (ResultCode) buffer.getUInt32();
}


Cql3Result::Cql3Result(): 
    _resultData(0),_resultCode(ResultCode::RESULT_ZERO_INFO)
{
}

Cql3Result::Cql3Result(const Cql3Result& result)
{
    _resultData = result._resultData;
    _resultCode = result._resultCode;
}

Cql3Result& Cql3Result::operator=(const Cql3Result& result)
{
    if (this != &result) {
        _resultData = result._resultData;
        _resultCode = result._resultCode;
    }
    return *this;
}

Cql3Result::~Cql3Result()
{
    _resultData = 0;
}

void Cql3Result::setBuffer(ByteBuffer& buffer)
{
    _resultData = &buffer;
    _resultCode = (ResultCode) buffer.getUInt32();
}

ResultCode Cql3Result::getResultCode() const
{
    return _resultCode;
}
