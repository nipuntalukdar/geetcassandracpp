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

#ifndef __GEETCASS_CQL3RESULT__
#define __GEETCASS_CQL3RESULT__
#include <bytebuffer.hpp>
#include <cql3cons.hpp>
#include <cql3header.hpp>
#include <encode.hpp>

namespace GeetCass
{

class Cql3Result 
{
public:
    Cql3Result(ByteBuffer& buffer);
    Cql3Result();
    Cql3Result(const Cql3Result& result);
    Cql3Result& operator=(const Cql3Result& result);
    void setBuffer(ByteBuffer& buffer);
    ResultCode getResultCode() const;
    ~Cql3Result();
private:
    ByteBuffer* _resultData;
    ResultCode _resultCode;
};
}  // GeetCass napespace ends

#endif
