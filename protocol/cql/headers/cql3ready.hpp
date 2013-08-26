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

#ifndef __CQL3READY__
#define __CQL3READY__
#include <bytebuffer.hpp>
#include <cql3header.hpp>

using GeetPutula::ByteBuffer;

namespace GeetCass
{

class Cql3Ready
{
public:
    static bool isValid(const ByteBuffer& buffer);
    static bool isValid(const void *buffer, size_t size); 
    static bool isValid(const Cql3Header& header);

};
} // namespace GeetCass ends
#endif
