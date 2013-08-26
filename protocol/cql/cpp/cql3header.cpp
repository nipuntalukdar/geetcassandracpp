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

#include <cql3header.hpp>

bool GeetCass::Cql3Header::encode(ByteBuffer& buffer)
{
    return (buffer.putChar(_version) && buffer.putChar(_flags) && buffer.putChar(_stream) &&
            buffer.putChar((char)_opcode) && buffer.putUInt32(_length));
}

void GeetCass::Cql3Header::setLength(uint32_t len)
{
    _length = len;
}
