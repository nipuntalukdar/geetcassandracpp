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

#ifndef __GEETCASS_CQL3QUERY__
#define __GEETCASS_CQL3QUERY__
#include <string>
#include <cql3cons.hpp>
#include <cql3header.hpp>
#include <cql3requestbody.hpp>
#include <encode.hpp>

using std::string;

namespace GeetCass
{

class Cql3Query : public Encode, public Cql3RequestBody
{
public:
    Cql3Query(const string& query, ConsistencyLevel level = ConsistencyLevel::ANY);
    virtual ~Cql3Query();
    virtual uint16_t getSize();
    virtual bool encode(ByteBuffer& buffer);
    void setQuery(const string& query);
private:
    string _query;
    ConsistencyLevel _level;
    uint16_t _size;
};

}  // GeetCass napespace ends

#endif
