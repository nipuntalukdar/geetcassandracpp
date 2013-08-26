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

#include <stdlib.h>
#include <string.h>
#ifndef __USE_BSD
#define __USE_BSD
#endif
#include <endian.h>
#include <bytebuffer.hpp>

using GeetPutula::ByteBufferException;

GeetPutula::ByteBuffer::ByteBuffer(size_t size, Endian endian, void* foreign_data, 
        size_t foreign_data_size)
{
    if (foreign_data) {
        _size = foreign_data_size;
        _isforeign = true;
    } else {
        _isforeign = false;
        _size = size;
    }
    if (_size == 0)
        throw ByteBufferException("Invalid data size");
    _position = 0;
    _endian = endian;
    if (!_isforeign)
        _data = calloc(1, size);
    else 
        _data = foreign_data;
}

GeetPutula::ByteBuffer::ByteBuffer(const ByteBuffer& buffer)
{
    _size = buffer._size;
    _position = buffer._position;
    _endian = buffer._endian;
    _data = malloc(_size);
    memcpy(_data, buffer._data, _size);
    _isforeign = false;
}

GeetPutula::ByteBuffer& GeetPutula::ByteBuffer::operator=(const ByteBuffer& buffer)
{
    if (this != &buffer) {
        _size = buffer._size;
        _position = buffer._position;
        _endian = buffer._endian;
        if (_data && !_isforeign)
            free(_data);
        _data = malloc(_size);
        memcpy(_data, buffer._data, _size);
        _isforeign = false;
    }
    return *this;
}

void GeetPutula::ByteBuffer::resize(size_t size) 
{
    void *temp = calloc(1, size);
    memcpy(temp, _data, _size > size ? size : _size);
    if (!_isforeign)
        free(_data);
    _data = temp;
    _size = size;
}

bool GeetPutula::ByteBuffer::putInt32(int32_t val, size_t position)
{
    int32_t converted = 0;
    if (_endian == BIG) 
        converted = htobe32(val);
    else
        converted = htole32(val);
    return putBytes((const void *)&converted, 4, position);
}

int32_t GeetPutula::ByteBuffer::getInt32(size_t position)
{
    int32_t val = 0;
    readBytes((void *)&val, 4, position);
    if (_endian == BIG) 
        return be32toh(val);
    return le32toh(val);
}

bool GeetPutula::ByteBuffer::putInt16(int16_t val, size_t position)
{
    int16_t converted = 0;
    if (_endian == BIG) 
        converted = htobe16(val);
    else
        converted = htole16(val);
    return putBytes((const void *)&converted, 2, position);
}

int16_t GeetPutula::ByteBuffer::getInt16(size_t position)
{
    int16_t val = 0;
    readBytes((void *)&val, 2, position);
    if (_endian == BIG) 
        return be16toh(val);
    return le16toh(val);
}

bool GeetPutula::ByteBuffer::putInt64(int64_t val, size_t position)
{
    int64_t converted = 0;
    if (_endian == BIG) 
        converted = htobe64(val);
    else
        converted = htole64(val);
    return putBytes((const void *)&converted, 8, position);
}

int64_t GeetPutula::ByteBuffer::getInt64(size_t position)
{
    int64_t val = 0;
    readBytes((void *)&val, 8, position);
    if (_endian == BIG) 
        return be64toh(val);
    return le64toh(val);
}

bool GeetPutula::ByteBuffer::putUInt32(uint32_t val, size_t position)
{
    return putInt32((int32_t)val, position);
}

uint32_t GeetPutula::ByteBuffer::getUInt32(size_t position)
{
    return (uint32_t) getInt32(position);
}

bool GeetPutula::ByteBuffer::putUInt16(uint16_t val, size_t position)
{
    return putInt16((int16_t)val, position);
}

uint16_t GeetPutula::ByteBuffer::getUInt16(size_t position)
{
    return (uint16_t) getInt16(position);
}

bool GeetPutula::ByteBuffer::putUInt64(uint64_t val, size_t position)
{
    return putInt64((int64_t)val, position);
}

uint64_t GeetPutula::ByteBuffer::getUInt64(size_t position)
{
    return (uint64_t)getInt64(position);
}

bool GeetPutula::ByteBuffer::putDouble(double val, size_t position)
{
    position = adjustPosition(position);
    if ((position + sizeof(double)) > _size)
        return false;
    if (((_endian == BIG) && littleEndianHost()) ||
            ((_endian == LITTLE) && !littleEndianHost())) {
        // swap needed
        int i = 0, j = sizeof(double);
        char *ptr = (char *)&val;
        while (i < j){
            *((char *)_data + position + i) = *(ptr + j - i -1);
            i++;
        }
    } else {
        memcpy((char *)_data + _position, (void *)&val, sizeof(double));
    }
    _position = position + sizeof(double);
    return true;
}

double GeetPutula::ByteBuffer::getDouble(size_t position)
{
    double val = 0.0;
    position = adjustPosition(position);

    if ((position + sizeof(double)) > _size)
        throw ByteBufferException("Cannot get a double from current position");
    if (((_endian == BIG) && littleEndianHost()) ||
            ((_endian == LITTLE) && !littleEndianHost())) {
        int i = 0, j = sizeof(double);
        char *ptr = (char *)&val;
        while (i < j){
            *(ptr + j - i -1) = *((char *)_data + position + i);
            i++;
        }
    } else {
        memcpy((void *)&val, (char *)_data + _position, sizeof(double));
    }
    _position = position + sizeof(double);
    return val;
}

bool GeetPutula::ByteBuffer::putFloat(float val, size_t position)
{
    position = adjustPosition(position);
    if ((position + sizeof(float)) > _size)
        return false;
    if (((_endian == BIG) && littleEndianHost()) ||
            ((_endian == LITTLE) && !littleEndianHost())) {
        // swap needed
        int i = 0, j = sizeof(float);
        char *ptr = (char *)&val;
        while (i < j){
            *((char *)_data + position + i) = *(ptr + j - i -1);
            i++;
        }
    } else {
        memcpy((char *)_data + _position, (char *)&val, sizeof(float));
    }
    _position = position + sizeof(float);
    return true;
}

float GeetPutula::ByteBuffer::getFloat(size_t position)
{
    float val = 0.0;
    position = adjustPosition(position);

    if ((position + sizeof(float)) > _size)
        throw ByteBufferException("Cannot get a float from current position");
    if (((_endian == BIG) && littleEndianHost()) ||
            ((_endian == LITTLE) && !littleEndianHost())) {
        // swap needed
        int i = 0, j = sizeof(float);
        char *ptr = (char *)&val;
        while (i < j){
            *(ptr + j - i -1) = *((char *)_data + position + i);
            i++;
        }
    } else {
        memcpy((void *)&val, (char *)_data + _position, sizeof(float));
    }
    _position = position + sizeof(float);
    return val;
}

bool GeetPutula::ByteBuffer::putChar(char c, size_t position)
{
    return putBytes((const void *)&c, sizeof(char), position);
}

int8_t GeetPutula::ByteBuffer::getInt8(size_t position)
{
    int8_t val = 0;
    readBytes((void *)&val, sizeof(int8_t), position);
    return val;
}

uint8_t GeetPutula::ByteBuffer::getUInt8(size_t position)
{
    uint8_t val = 0;
    readBytes((void *)&val, sizeof(uint8_t), position);
    return val;
}

char GeetPutula::ByteBuffer::getChar(size_t position)
{
    char val = '0';
    readBytes((void *)&val, sizeof(char), position);
    return val;
}

bool GeetPutula::ByteBuffer::putWChar(wchar_t c, size_t position)
{
    return putBytes((const void*)&c, sizeof(wchar_t), position);
}

wchar_t GeetPutula::ByteBuffer::getWChar(size_t position)
{
    wchar_t val = '0';
    readBytes((void *)&val, sizeof(wchar_t), position);
    return val;
}

GeetPutula::ByteBuffer::~ByteBuffer()
{
    if (_data && !_isforeign)
        free(_data);
}

void GeetPutula::ByteBuffer::rewind()
{
    _position = 0;
}

size_t GeetPutula::ByteBuffer::position(size_t newposition)
{
    size_t oldposition = _position;
    if (newposition > _size)
        _position = _size;
    else
        _position = newposition;
    return oldposition;
}

bool GeetPutula::ByteBuffer::putBytes(const void *bytes, size_t size, size_t position)
{
    position = adjustPosition(position); 
    if ((position + size ) > _size)
        return false;
    memcpy((void *)((char *)_data + _position), bytes, size);
    _position = position + size;
    return true;
}

void GeetPutula::ByteBuffer::readBytes(void *dest, size_t size, size_t position)
{
    position = adjustPosition(position);
    if ((_position + size ) > _size)
        throw ByteBufferException("Not enough data to read");
    memcpy(dest , (char *)_data + _position, size);
    _position = position + size;
}

void GeetPutula::ByteBuffer::proceed(size_t steps)
{
    if ((_position + steps) > _size )
        throw ByteBufferException("Overflow error");
    _position += steps;
}

void GeetPutula::ByteBuffer::back(size_t steps)
{
    if (_position < steps)
        throw ByteBufferException("Underflow error");
    _position -= steps;
}

size_t GeetPutula::ByteBuffer::copyRaw(void *output, size_t start, size_t maxbytes) const
{
    if (!output || (start >= _size) || (maxbytes == 0))
        return 0;
    maxbytes = ((start + maxbytes) > _size) ? (_size - start + 1) :
                        maxbytes;
    memcpy(output, (char *)_data + start , maxbytes);
    
    return maxbytes;
}



bool GeetPutula::ByteBuffer::littleEndianHost()
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return true;
#else
    return false;
#endif
}
