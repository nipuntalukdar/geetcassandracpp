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

#ifndef __GEETCASS_ENCODE__
#define __GEETCASS_ENCODE__

#include <bytebuffer.hpp>
using GeetPutula::ByteBuffer;

namespace GeetCass
{

class Encode
{
public:
    virtual bool encode(ByteBuffer& buffer) = 0;
};
}  // GeetCass napespace ends
#endif
