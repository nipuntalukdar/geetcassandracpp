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

#ifndef __GEETPUTULA_BYTEBUFFER__
#define __GEETPUTULA_BYTEBUFFER__

#include <inttypes.h>
#include <stdint.h>
#include <bytebuffer_exception.hpp>

#ifndef SIZE_MAX
#define SIZE_MAX (size_t) (-1)
#endif

namespace GeetPutula
{

class ByteBuffer
{
public:
    enum Endian{
        BIG, 
        LITTLE
    };

    ByteBuffer(size_t size = 256, Endian endian = BIG, void *foreign_data = 0,
            size_t foreign_data_size = 0);
    ByteBuffer(const ByteBuffer&);
    ByteBuffer& operator=(const ByteBuffer&);
    void resize(size_t size);

    // position SIZE_MAX indicates operation starts at cyrrent
    // position
    bool putInt32(int32_t val, size_t position = SIZE_MAX);
    int32_t getInt32(size_t position = SIZE_MAX);
    bool putInt16(int16_t val, size_t position = SIZE_MAX);
    int16_t getInt16(size_t position = SIZE_MAX);
    bool putInt64(int64_t val, size_t position = SIZE_MAX);
    int64_t getInt64(size_t position = SIZE_MAX);
    bool putUInt32(uint32_t val, size_t position = SIZE_MAX);
    uint32_t getUInt32(size_t position = SIZE_MAX);
    bool putUInt16(uint16_t val, size_t position = SIZE_MAX);
    uint16_t getUInt16(size_t position = SIZE_MAX);
    bool putUInt64(uint64_t val, size_t position = SIZE_MAX);
    uint64_t getUInt64(size_t position = SIZE_MAX);
    bool putFloat(float val, size_t position = SIZE_MAX);
    float getFloat(size_t position = SIZE_MAX);
    bool putDouble(double val, size_t position = SIZE_MAX);
    double getDouble(size_t position = SIZE_MAX);
    bool putChar(char val, size_t position = SIZE_MAX);
    char getChar(size_t position = SIZE_MAX);
    int8_t getInt8(size_t position = SIZE_MAX);
    uint8_t getUInt8(size_t position = SIZE_MAX);
    bool putWChar(wchar_t val, size_t position = SIZE_MAX);
    wchar_t getWChar(size_t position = SIZE_MAX);
    bool putBytes(const void *bytes, size_t size, size_t position = SIZE_MAX);
    void readBytes(void *dest, size_t size, size_t position = SIZE_MAX);

    void rewind();
    size_t position(size_t newposition);
    size_t currentPosition() const;
    void proceed(size_t steps);
    void back(size_t steps);
    size_t copyRaw(void *output, size_t start, size_t maxbytes) const;
    void* getRaw() const;
    size_t remaining() const;
    size_t capacity() const;
    void reset(); 

    ~ByteBuffer();

private:
    size_t _size;
    size_t _position;
    void *_data;
    Endian _endian;
    bool _isforeign;
   
    static bool littleEndianHost(); 
    size_t adjustPosition(size_t position) const;

};

inline size_t ByteBuffer::currentPosition() const
{
    return _position;
}

inline size_t ByteBuffer::remaining() const
{
    return (_size - _position);
}

inline size_t ByteBuffer::capacity() const
{
    return _size;
}

inline void ByteBuffer::reset() 
{
    _position = 0;    
}

inline size_t ByteBuffer::adjustPosition(size_t position) const
{
    return position == SIZE_MAX ? _position : position;
}

inline void* ByteBuffer::getRaw() const
{
    return _data;
}

} // namespace close

#endif
