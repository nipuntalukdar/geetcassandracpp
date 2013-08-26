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

#include <cql3errordecode.hpp>
#include <utility.hpp>

using namespace GeetCass;

Cql3ErrorMsg::Cql3ErrorMsg():
    _errorMsg(""), _keySpace(""), _table(""), _errorCode(ErrorCode::SERVER_ERROR)
{
}

ErrorCode Cql3ErrorDecode::_getErrorCode(ByteBuffer& buffer)
{
    if (buffer.remaining() < sizeof(ErrorCode))
        throw ByteBufferException("Invalid size");
    return (ErrorCode) buffer.getUInt32();
}

void Cql3ErrorDecode::_getProtocolError(ByteBuffer& buffer, string& errorStr)
{
    Utility::readShortString(buffer, errorStr);
}

void Cql3ErrorDecode::_getServerError(ByteBuffer& buffer, string& errorStr)
{
    Utility::readShortString(buffer, errorStr);
}

void Cql3ErrorDecode::_getSyntaxError(ByteBuffer& buffer, string& errorStr)
{
    Utility::readShortString(buffer, errorStr);
}

void Cql3ErrorDecode::_getInvalidQueryError(ByteBuffer& buffer, string& errorStr)
{
    Utility::readShortString(buffer, errorStr);
}

void Cql3ErrorDecode::decodeErrorMsg(ByteBuffer& buffer, Cql3ErrorMsg& out)
{
    ErrorCode error = _getErrorCode(buffer);
    switch (error) {
        case ErrorCode::PROTOCOL_ERROR:
            _getProtocolError(buffer, out.getErrorMsg());
            break;
        case ErrorCode::SERVER_ERROR:
            _getServerError(buffer, out.getErrorMsg());
            break;
        case ErrorCode::SYNTAX_ERROR:
            _getSyntaxError(buffer, out.getErrorMsg());
            break;
        case ErrorCode::INVALID_QUERY:
            _getInvalidQueryError(buffer, out.getErrorMsg());
            break;
        default:
            cout << (uint32_t)error << endl;
            break;
    }
}
