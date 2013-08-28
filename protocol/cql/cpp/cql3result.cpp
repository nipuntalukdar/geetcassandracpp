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

using namespace GeetCass;

void Cql3RowMetaData::init(ByteBuffer& buffer, Cql3RowMetaData& metadata)
{
    metadata.flags = buffer.getInt32();
    metadata.column_count = buffer.getInt32();
    if (GLOBAL_TABLE_SPEC_PRESENT == metadata.flags) {
        Utility::readShortString(buffer, metadata.global_table_spec[0]);
        Utility::readShortString(buffer, metadata.global_table_spec[1]);
    }
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
    if (ResultCode::RESULT_ROWS == _resultCode){
        Cql3RowMetaData metadata;
        metadata.init(buffer, metadata);
    }
}

ResultCode Cql3Result::getResultCode() const
{
    return _resultCode;
}
