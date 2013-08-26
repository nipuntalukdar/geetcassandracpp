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

#include <cql3ready.hpp>

bool GeetCass::Cql3Ready::isValid(const ByteBuffer& buffer)
{
    if (buffer.capacity() < CQL_HEADER_SIZE){
        return false;
    } 
    Cql3Header *header = (Cql3Header *)buffer.getRaw();
    
   return isValid(*header); 
}

bool GeetCass::Cql3Ready::isValid(const void* buffer, size_t size)
{
    if (size < CQL_HEADER_SIZE){
        return false;
    } 
    Cql3Header *header = (Cql3Header *)buffer;
    
   return isValid(*header); 
}

bool GeetCass::Cql3Ready::isValid(const Cql3Header& header) 
{
    return (header.getVersion() == RESPONSE_VERSION &&
            header.getOpcode() == OpCode::READY &&
            header.getBodyLength() == 0);
}
