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

#ifndef __GEETCASS_CQL3RESPONSE__
#define __GEETCASS_CQL3RESPONSE__
#include <cql3cons.hpp>
#include <cql3header.hpp>
#include <cql3result.hpp>
#include <encode.hpp>
#include <utility.hpp>

namespace GeetCass
{

class Cql3Response 
{
public:
    static Cql3Header* decodeResponse(ByteBuffer& buffer);
    static void decodeSupported(ByteBuffer& buffer, map<string, list<string> >& str);
    static void decodeAuthenticate(ByteBuffer& buffer, string& auth_class_inuse);
    static void decodeResult(ByteBuffer& buffer, Cql3Result& result);
};

}  // GeetCass napespace ends

#endif
