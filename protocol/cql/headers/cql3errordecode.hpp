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

#ifndef __CQL3ERRORDECODE__
#define __CQL3ERRORDECODE__

#include <iostream>
#include <string>
#include <cql3cons.hpp>
#include <bytebuffer.hpp>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using GeetPutula::ByteBuffer;

namespace GeetCass
{

class Cql3ErrorMsg
{
public:
    Cql3ErrorMsg();
    Cql3ErrorMsg(const Cql3ErrorMsg& msg);
    Cql3ErrorMsg& operator = (Cql3ErrorMsg& msg);
    friend ostream& operator << (ostream& os, const Cql3ErrorMsg& msg) {
        os << msg._errorMsg << " " 
            << msg._keySpace << " ";
            //<< msg._table << " " << msg._errorCode;
        return os;
    }
    string& getErrorMsg();
private:
   string _errorMsg;
   string _keySpace;
   string _table;
   ErrorCode _errorCode;
};

inline string& Cql3ErrorMsg::getErrorMsg()
{
    return _errorMsg;
}

class Cql3ErrorDecode
{
public:
    static void decodeErrorMsg(ByteBuffer& buffer, Cql3ErrorMsg& out);
private:
    static ErrorCode _getErrorCode(ByteBuffer& buffer); 
    static void _getProtocolError(ByteBuffer& buffer, string& errStr);
    static void _getServerError(ByteBuffer& buffer, string& errStr);
    static void _getSyntaxError(ByteBuffer& buffer, string& errStr);
    static void _getInvalidQueryError(ByteBuffer& buffer, string& errStr);
};

} // namespace GeetCass ends

#endif 
