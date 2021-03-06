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

#ifndef __GEETCASS_CONNECTION__
#define __GEETCASS_CONNECTION__

#include <string>
#include <boost/asio.hpp>
#include <bytebuffer.hpp>


using GeetPutula::ByteBuffer;
using std::string;

namespace GeetCass 
{

class Connection
{
public:
    Connection(const string& host, uint16_t port);
    Connection();
    uint32_t write(const void *data, size_t size);
    uint32_t write(const ByteBuffer& buffer, size_t size) const;
    uint32_t read(void* data, size_t max_bytes);
    uint32_t read(ByteBuffer& buffer, size_t max_bytes); 
    void close();
    bool open();
    ~Connection();
private:
    string _host;
    uint16_t _port;
    bool _isopen;
    void *_pvt;
};

} // namespace GeetCass ends

#endif
