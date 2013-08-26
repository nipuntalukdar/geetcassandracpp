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

#include <cql3start.hpp>

GeetCass::Cql3Start::Cql3Start(const string& version, const string& comproption):
    _cql3version(version), _compression(comproption)
{
    _size = 2;
    _size += CQL_VERSION_KEY.size() + _cql3version.size() + 4;
    if (_compression != "") {
        _size += COMPRESSION_KEY.size() +  _compression.size() + 4;
    }
}

uint16_t GeetCass::Cql3Start::getSize()
{
    return _size;
}

bool GeetCass::Cql3Start::encode(ByteBuffer& buffer)
{
    if (_compression != "") {
        buffer.putUInt16(2);
    } else {
        buffer.putUInt16(1);
    }
    buffer.putUInt16((uint16_t)CQL_VERSION_KEY.size());
    buffer.putBytes((void *)CQL_VERSION_KEY.c_str(),CQL_VERSION_KEY.size());
    buffer.putUInt16((uint16_t)_cql3version.size());
    buffer.putBytes((void *)_cql3version.c_str(), _cql3version.size());
    
    if (_compression != ""){
        buffer.putUInt16((uint16_t)COMPRESSION_KEY.size());
        buffer.putBytes((void *)_cql3version.c_str(), _compression.size());
    }
    return true;
}

GeetCass::Cql3Start::~Cql3Start()
{
    _size = 0;
}

