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

#ifndef __CQL3ERRORMSG__
#define __CQL3ERRORMSG__

#include <iostream>
#include <string>
#include <bytebuffer.hpp>
#include <bytebuffer_exception.hpp>
using GeetPutula::ByteBuffer;
using GeetPutula::ByteBufferException;
using std::string;
using std::ostream;

namespace GeetCass
{
class Cql3ErrorMsg
{
public:
    Cql3ErrorMsg(ByteBuffer& buffer);
    Cql3ErrorMsg(const Cql3ErrorMsg& msg);
    Cql3ErrorMsg& operator = (Cql3ErrorMsg& msg);
    ostream& operator << (ostream& os) {
        os << _errorMsg << " " 
            << _keySpace << " "
            << _table << " " << _errorCode;
        return os;
    }

private:
   ByteBuffer& _buffer;
   string _errorMsg;
   string _keySpace;
   string _table;
   uint16_t _errorCode;
};

} // namespace GeetCass ends

#endif
