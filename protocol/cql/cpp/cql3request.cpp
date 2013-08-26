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

#include <cql3request.hpp>
#include <cql3start.hpp>
#include <cql3query.hpp>

GeetCass::Cql3Request::Cql3Request(Cql3Header *header, Cql3RequestBody *body)
{
    _header = header;
    _body = body;
    _header->setLength(_body->getSize());
    _opcode = _header->getOpcode();
}

GeetCass::Cql3Request::~Cql3Request()
{
    if (_header)
        delete _header;
    if (_body)
        delete _body;
}

bool GeetCass::Cql3Request::encode(ByteBuffer& buffer)
{
    _header->encode(buffer);
    _body->encode(buffer);
    return true;
}

size_t GeetCass::Cql3Request::getSize() const
{
    return (size_t) (_header->getSize() + _body->getSize());
}

