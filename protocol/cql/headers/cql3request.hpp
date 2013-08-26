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

#ifndef __GEETCASS_CQL3REQUEST__
#define __GEETCASS_CQL3REQUEST__
#include <cql3cons.hpp>
#include <cql3header.hpp>
#include <cql3requestbody.hpp>
#include <encode.hpp>

namespace GeetCass
{

class Cql3Request : public Encode
{
public:
    Cql3Request(Cql3Header *header, Cql3RequestBody *body);
    ~Cql3Request();
    virtual bool encode(ByteBuffer& buffer);
    size_t getSize() const;

private:
    OpCode _opcode;
    Cql3Header *_header;    
    Cql3RequestBody *_body;
};

}  // GeetCass napespace ends

#endif
