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

#ifndef __GEETCASS_CQL3CONS__
#define __GEETCASS_CQL3CONS__
#include <stdint.h>
#include <string>

using std::string;

namespace GeetCass
{
enum class OpCode : uint8_t{
     ERROR = 0x00,
     STARTUP = 0x01,
     READY = 0x02,
     AUTHENTICATE = 0x03,
     CREDENTIALS = 0x04,
     OPTIONS = 0x05,
     SUPPORTED = 0x06,
     QUERY = 0x07,
     RESULT = 0x08,
     PREPARE = 0x09,
     EXECUTE = 0x0A,
     REGISTER = 0x0B,
     EVENT = 0x0C
}; 

const uint32_t CQL_HEADER_SIZE = 8;
const uint8_t COMPRESSION = 0x01;
const uint8_t TRACE = 0x02;
const uint8_t REQUEST_VERSION = 0x01;
const uint8_t RESPONSE_VERSION = 0x81;
const string CQL_VERSION_KEY =  "CQL_VERSION";
const string CURRENT_CQL_VERSION = "3.0.0";
const string COMPRESSION_KEY = "COMPRESSION";
const uint32_t GLOBAL_TABLE_SPEC_PRESENT = 1;

enum class ConsistencyLevel : uint16_t {
    ANY = 0x0000,
    ONE = 0x0001,
    TWO = 0x0002,
    THREE = 0x0003,
    QUORUM = 0x0004,
    ALL = 0x0005,
    LOCAL_QUORUM = 0x0006,
    EACH_QUORUM = 0x0007
};

enum class ErrorCode : uint32_t {
    SERVER_ERROR = 0x0000, 
    PROTOCOL_ERROR = 0x000A,
    BAD_CREDENTIAL = 0x0100,
    UNAVAILABLE_EXCEPTION = 0x1000,
    COORDINATOR_OVERLOADED = 0x1001, 
    COORDINATOR_BOOTSTRAPPING = 0x1002,
    TRUNCATE_ERROR = 0x1003,
    WRITE_TIMEOUT = 0x1100,
    READ_TIMEOUT = 0x1200,
    SYNTAX_ERROR = 0x2000,
    UNAUTHORIZED = 0x2100,
    INVALID_QUERY = 0x2200,
    CONFIG_ERROR = 0x2300,
    ALREADY_EXISTS = 0x2400,
    UNPREPARED_QUERY = 0x2500
};

enum class ResultCode : uint32_t {
    RESULT_ZERO_INFO =  0x0001,
    RESULT_ROWS = 0x0002,
    RESULT_SET_KEYSPACE = 0x0003,
    RESULT_PREPARED = 0x0004,
    RESULT_SCHEMA_CHANGED = 0x0005
};

enum class Cql3Types : uint16_t {
    CUSTOM = 0x0000,
    ASCII = 0x0001,
    BIGINT = 0x0002,
    BLOB = 0x0003,
    BOOLEAN = 0x0004,
    COUNTER = 0x0005,
    DECIMAL = 0x0006,
    DOUBLE = 0x0007,
    FLOAT = 0x0008,
    INT = 0x0009,
    TEXT = 0x000A,
    TIMESTAMP = 0x000B,
    UUID = 0x000C,
    VARCHAR = 0x000D,
    VARINT = 0x000E,
    TIMEUUID = 0x000F,
    INET = 0x0010,
    LIST = 0x0020,
    MAP = 0x0021,
    SET = 0x0022
};

}  // GeetCass napespace ends

#endif
