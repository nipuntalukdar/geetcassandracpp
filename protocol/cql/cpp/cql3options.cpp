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

#include <cql3options.hpp>

GeetCass::Cql3Options::Cql3Options():
    _size(0)
{
}

GeetCass::Cql3Options::Cql3Options(const Cql3Options& options){
    (void)options;
    _size = 0;
}

GeetCass::Cql3Options& GeetCass::Cql3Options::operator=(const Cql3Options& options){
    (void)options;
    return *this;
}

uint16_t GeetCass::Cql3Options::getSize()
{
    return _size;
}

bool GeetCass::Cql3Options::encode(ByteBuffer& buffer)
{
    (void) buffer;
    return true;
}

GeetCass::Cql3Options::~Cql3Options()
{
    _size = 0;
}
