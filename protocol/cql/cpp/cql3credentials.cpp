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

#include <cql3credentials.hpp>

GeetCass::Cql3Credentials::Cql3Credentials(map<string, string>& credentials):
    _credentials(credentials)
{
    _size = 2 + ((credentials.size()) * 4);
    map<string,string>::iterator it = credentials.begin();
    while (it != credentials.end()){
        _size += it->first.size() + it->second.size();
        ++it;
    }
}

uint16_t GeetCass::Cql3Credentials::getSize()
{
    return _size;
}

bool GeetCass::Cql3Credentials::encode(ByteBuffer& buffer)
{
    buffer.putUInt16(_credentials.size());
    map<string,string>::iterator it = _credentials.begin();
    while (it != _credentials.end()){
        buffer.putInt16(it->first.size());
        buffer.putBytes(it->first.c_str(),it->first.size());
        buffer.putInt16(it->second.size());
        buffer.putBytes(it->second.c_str(),it->second.size());
        ++it;
    }
    return true;
}

GeetCass::Cql3Credentials::~Cql3Credentials()
{
    _size = 0;
}
