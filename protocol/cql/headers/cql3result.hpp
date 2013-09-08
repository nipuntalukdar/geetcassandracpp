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

#ifndef __GEETCASS_CQL3RESULT__
#define __GEETCASS_CQL3RESULT__
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <bytebuffer.hpp>
#include <cql3cons.hpp>
#include <cql3header.hpp>
#include <encode.hpp>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

namespace GeetCass
{

struct Column
{
    string column;
    Cql3Types column_type;

    Column(const string& col, Cql3Types type) : column(col), column_type(type)
    {
    }

    Column() : column(""), column_type(Cql3Types::INT) 
    {
    }

    string& getColumnName() {
        return column;
    }

    Cql3Types getColumnType(){
        return column_type;
    }
};

class Cql3RowMetaData
{
public:
    static void init(ByteBuffer& buffer, Cql3RowMetaData& metadata);
    Cql3RowMetaData() {
        _flags = 0;
        _column_count = 0;
        _column_count = 0;
    }
    ~Cql3RowMetaData();
    Column* getColumn(size_t index) const throw (char *);
    uint32_t getColumnCount() const 
    {
        return _column_count;
    }

    uint32_t getRowCount() const 
    {
        return _row_count;
    }
private:
    uint32_t _flags;
    uint32_t _column_count;
    uint32_t _row_count;
    string _global_table_spec[2];
    vector <Column *> _columns;
};

struct ColumnHash 
{
    size_t operator()(Column* const &c) const {
        if (0 == c)
            return 0;
        return std::hash<string>()(c->column);
    }
};

struct ColumnEq 
{
    bool operator()(Column* const & a1, Column* const& a2 ) const{
        if (a1 == 0 && a2 == 0){
            return true;
        } else if (a1 && a2) {
            return a1->column == a2->column;
        } else {
            return false;
        }
    }
};


class Cql3Row : public boost::noncopyable
{
public:
    Cql3Row(void *buffer = 0, size_t size = 0, unordered_map<Column*, size_t,
            ColumnHash, ColumnEq>* columnpos =0);
    bool getString(const string& column, string& out);
    bool getInt(const string& column, int32_t& val);
    ~Cql3Row();
private:
    std::unordered_map<Column*, size_t, ColumnHash, ColumnEq >* _columnPositions;
    size_t _row_size;
    void*  _data;
    ByteBuffer *_buffer;

};

class Cql3Rows : public boost::noncopyable
{
public:
    static void init(ByteBuffer& buffer, Cql3Rows& rows, size_t max_pos);
    uint32_t getRowCount() const;
    Cql3Row* getNextRow();
    Cql3Row* getRow(uint32_t rowNum);
    Cql3Rows(ByteBuffer* buffer = 0, size_t start = 0, size_t stop = 0) :
        _buffer(buffer), _startInByteBuffer(start), _stopInByteBuffer(stop)
    {
    }

private:
    ByteBuffer *_buffer;
    size_t _startInByteBuffer;
    size_t _stopInByteBuffer;
    Cql3RowMetaData _metaData;
    uint32_t _currentRow;
    vector <int> _rowPositions;
};

class Cql3Result 
{

public:
    Cql3Result(ByteBuffer& buffer);
    Cql3Result();
    Cql3Result(const Cql3Result& result);
    Cql3Result& operator=(const Cql3Result& result);
    void setBuffer(ByteBuffer& buffer);
    ResultCode getResultCode() const;
    ~Cql3Result();

private:
    ByteBuffer* _resultData;
    ResultCode _resultCode;
};
}  // GeetCass napespace ends

#endif
