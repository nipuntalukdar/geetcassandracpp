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

#ifndef __GEETCASS_CQL3HEADER__
#define __GEETCASS_CQL3HEADER__

#include <cql3cons.hpp>
#include <bytebuffer.hpp>
#include <encode.hpp>

using GeetPutula::ByteBuffer;

namespace GeetCass
{

class  Cql3Header : public Encode
{
public:
    Cql3Header(uint8_t version, uint8_t flags, uint8_t stream, OpCode opcode, uint32_t length = 0):
        _version(version), _flags(flags), _stream(stream), _opcode(opcode),
        _length(length)
    {
    }
    virtual bool encode(ByteBuffer& buffer);
    uint8_t getVersion() const;
    uint8_t getFlags() const;
    uint8_t getStreamId() const;
    OpCode getOpcode() const;
    uint32_t getBodyLength() const;
    size_t getSize() const;
    void setLength(uint32_t length);

private:
    uint8_t _version;
    uint8_t _flags;
    uint8_t _stream;
    OpCode _opcode;
    uint32_t _length;
 
};


inline size_t Cql3Header::getSize() const
{
    return 8;
}

inline uint8_t Cql3Header::getVersion() const
{
    return _version;
}

inline uint8_t Cql3Header::getFlags() const
{
    return _flags;
}

inline uint8_t Cql3Header::getStreamId() const
{
    return _stream;
}

inline OpCode Cql3Header::getOpcode() const
{
    return _opcode;
}

inline uint32_t Cql3Header::getBodyLength() const
{
    return _length;
}

}  // GeetCass napespace ends
#endif
