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

#include <cql3errormsg.hpp>
GeetCass::Cql3ErrorMsg::Cql3ErrorMsg(ByteBuffer& buffer):
    _buffer(buffer) 
{
    _errorCode = 0;
    _errorMsg = "";
    _keySpace = "";
    _table = "";
   if (buffer.remaining() < 8)
       throw ByteBufferException("Invalid byte buffer size");
   _errorCode = buffer.getUInt32(); 
   uint16_t message_size = buffer.getUInt16();
   
   if (buffer.remaining() < message_size)
       throw ByteBufferException("Invalid byte buffer size");
   _errorMsg = string((char *)(buffer.getRaw()) + buffer.currentPosition(), (size_t)message_size);
   
    do {
        // Now get the keyspace Name
        buffer.position(buffer.currentPosition() + message_size);
        message_size = buffer.getUInt16();
        if (message_size == 0)
            break;
        if (message_size > buffer.remaining()) {
            throw ByteBufferException("Not enough data ");
        }
        _keySpace = string((char *)(buffer.getRaw()) + buffer.currentPosition(), (size_t)message_size);

        // Now get the table Name
        buffer.position(buffer.currentPosition() + message_size);
        message_size = buffer.getUInt16();
        if (message_size == 0)
            break;
        if (message_size > buffer.remaining()) {
            throw ByteBufferException("Not enough data ");
        }
        _table = string((char *)(buffer.getRaw()) + buffer.currentPosition(), (size_t)message_size);
    }while(false);
}

