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

#include <boost/asio.hpp>
#include <connection.hpp>
#include <iostream>

using std::cout;
using std::endl;

using boost::asio::ip::tcp;
using boost::asio::ip::address;
using boost::asio::io_service;
using boost::system::error_code;

namespace GeetCass 
{
struct pvt_data
{
    io_service ios;  
    tcp::endpoint endpoint;
    tcp::socket socket;
    pvt_data(const string& host, uint16_t port):
        endpoint(address::from_string(host), port), socket(ios)
    {
    }
};    
}

GeetCass::Connection::Connection(const string& host, uint16_t port)
{
    _host = host;
    _port = port;
    _isopen = false;
    _pvt = new pvt_data(host, port);
    pvt_data *pd = (pvt_data *)_pvt;
    error_code error;
    pd->socket.connect(pd->endpoint, error);
    if (error){
        cout << boost::system::system_error(error).what() << endl;
        throw "some problem defininitely";
    }
} 

uint32_t GeetCass::Connection::write(const void *data, size_t size)
{
    error_code error;
    pvt_data *pd = (pvt_data *)_pvt;
    size_t written = boost::asio::write(pd->socket, boost::asio::buffer(data, size), 
            boost::asio::transfer_all(), error);
    if (error)
       return -1;

    return written;
}

uint32_t GeetCass::Connection::read(void *data, size_t max_bytes)
{
    error_code error;
    pvt_data *pd = (pvt_data *)_pvt;
    size_t readlen = pd->socket.read_some(boost::asio::buffer(data, max_bytes), 
           error);
    if (error)
       return -1;
    return readlen;
}

GeetCass::Connection::~Connection()
{
    pvt_data *pd = (pvt_data *)_pvt;
    pd->socket.close();
    pd->ios.stop();
}
