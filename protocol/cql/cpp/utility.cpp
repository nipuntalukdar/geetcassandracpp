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

#include <utility.hpp>

void GeetCass::Utility::readShortString(ByteBuffer& buffer, string& str)
{
    do {
        if (buffer.remaining() < sizeof(uint16_t))
            break;
        uint16_t sizeOfString = buffer.getUInt16();
        if (buffer.remaining() < (size_t) sizeOfString)
            break;
        str = string((char *)buffer.getRaw() + buffer.currentPosition(), (size_t) sizeOfString);
        buffer.position( buffer.currentPosition() + sizeOfString);
        return;
    } while (false);
    throw ByteBufferException("Invalid data size");
}

void GeetCass::Utility::readLongString(ByteBuffer& buffer, string& str)
{
    do {
        if (buffer.remaining() < sizeof(uint32_t))
            break;
        uint16_t sizeOfString = buffer.getUInt32();
        if (buffer.remaining() < (size_t) sizeOfString)
            break;
        str = string((char *)buffer.getRaw() + buffer.currentPosition(), (size_t)sizeOfString);
        buffer.position( buffer.currentPosition() + sizeOfString);
        return;
    } while (false);
    throw ByteBufferException("Invalid data size");
}

void GeetCass::Utility::readStringMap(ByteBuffer& buffer, map<string, string>& strs)
{
    do {
        string key = "";
        string val = "";
        if (buffer.remaining() < sizeof(uint16_t))
            break;
        uint16_t keyvalPairs = buffer.getUInt16(), i = 0;
        while (i++ < keyvalPairs) {
            readShortString(buffer, key);
            readShortString(buffer, val);
            strs[key] = val;
        }
        return;
    } while (false);
    throw ByteBufferException("Invalid data size");
}

void GeetCass::Utility::readStringList(ByteBuffer& buffer, list<string>& strs)
{
    do {
        string val = "";
        if (buffer.remaining() < sizeof(uint16_t))
            break;
        uint16_t numstring = buffer.getUInt16();
        while (numstring-- != 0) {
            readShortString(buffer, val);
            strs.push_back(val);
        }
        return;
    } while (false);
    throw ByteBufferException("Invalid data size");
}

void GeetCass::Utility::readStringMultiMap(ByteBuffer& buffer, map<string, list<string> >& strs)
{
    do {
        string key = "";
        list<string> vals;
        if (buffer.remaining() < sizeof(uint16_t))
            break;
        uint16_t keyvalPairs = buffer.getUInt16();
        while (keyvalPairs-- != 0) {
            readShortString(buffer, key);
            readStringList(buffer, vals);
            strs[key] = vals;
        }
        return;
    } while (false);
    throw ByteBufferException("Invalid data size");
}
