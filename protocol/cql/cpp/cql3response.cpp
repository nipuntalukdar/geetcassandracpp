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

#include <cql3response.hpp>

using namespace GeetCass;

Cql3Header* Cql3Response::decodeResponse(ByteBuffer& buffer)
{
    if (buffer.remaining() < CQL_HEADER_SIZE)
        throw "Not enough data to decode the response";
    return new Cql3Header(buffer.getUInt8(), buffer.getUInt8(),
            buffer.getUInt8(), (OpCode)buffer.getUInt8(),
            buffer.getUInt32());
}

void Cql3Response::decodeSupported(ByteBuffer& buffer, 
        map<string, list<string> >& strs)
{
    Utility::readStringMultiMap(buffer, strs);
}

void Cql3Response::decodeAuthenticate(ByteBuffer& buffer, 
        string& auth_class_inuse)
{
    Utility::readShortString(buffer, auth_class_inuse);
}

void Cql3Response::decodeResult(ByteBuffer& buffer, Cql3Result& result)
{
    result.setBuffer(buffer);
}
