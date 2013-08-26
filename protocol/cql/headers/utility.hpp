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

#ifndef __GEETCASS_UTILITY__
#define __GEETCASS_UTILITY__

#include <string>
#include <list>
#include <map>
#include <bytebuffer.hpp>
#include <bytebuffer_exception.hpp>

using std::string;
using std::map;
using std::list;
using std::multimap;

using GeetPutula::ByteBuffer;
using GeetPutula::ByteBufferException;

namespace GeetCass
{

class Utility 
{
public:
    static void readShortString(ByteBuffer& buffer, string& str);
    static void readLongString(ByteBuffer& buffer, string& str);
    static void readStringMap(ByteBuffer& buffer,  map<string, string>& strs);
    static void readStringList(ByteBuffer& buffer, list<string>& strs);
    static void readStringMultiMap(ByteBuffer& buffer, map<string, list<string> >& strs);
};

}  // GeetCass napespace ends

#endif
