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

#include <cql3query.hpp>

GeetCass::Cql3Query::Cql3Query(const string& query, ConsistencyLevel level):
    _query(query), _level(level)
{
    _size = 6 + _query.size(); // 6 = 4 + 2 , 4 for length of query, 2 for consistency level
}

uint16_t GeetCass::Cql3Query::getSize()
{
    return _size;
}

bool GeetCass::Cql3Query::encode(ByteBuffer& buffer)
{
    buffer.putUInt32((uint32_t)_query.size());
    buffer.putBytes((void *)_query.c_str(), _query.size());
    buffer.putUInt16((uint16_t)_level);
    return true;
}

GeetCass::Cql3Query::~Cql3Query()
{
    _size = 0;
}
