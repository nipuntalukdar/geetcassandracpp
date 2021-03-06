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

#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <iomanip>
#include <cql3cons.hpp>
#include <cql3request.hpp>
#include <cql3requestbody.hpp>
#include <cql3response.hpp>
#include <cql3header.hpp>
#include <cql3ready.hpp>
#include <cql3start.hpp>
#include <cql3query.hpp>
#include <cql3options.hpp>
#include <connection.hpp>
#include <cql3errordecode.hpp>
#include <cql3credentials.hpp>
#include <cql3result.hpp>
#include <utility.hpp>

using namespace std;
using namespace GeetCass;
using namespace GeetPutula;

int main()
{
    try {
        string query ;
        Cql3Header *header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::STARTUP);
        Cql3RequestBody *body = new Cql3Start();
        Cql3Request *request = new Cql3Request(header, body);      
        cout << request->getSize() << endl;
        ByteBuffer bf(request->getSize());
        request->encode(bf);
        Connection *conn = new Connection("127.0.0.1", 9042);
        conn->write(bf.getRaw(), bf.position(0));
        uint8_t read_data[25600];
        uint32_t read_size =  conn->read(read_data, 8);
        delete request;

        ByteBuffer bf3(0, ByteBuffer::BIG, read_data, 25600);
        Cql3Header *cheader  = Cql3Response::decodeResponse(bf3);
        if (Cql3Ready::isValid(*cheader)) {
            cout << "I got a valid response \n";
        } else if (cheader->getOpcode() == OpCode::AUTHENTICATE){
           cout << "This is an authenticate request , decode the authenticate request\n";
           bf3.rewind();
           read_size = conn->read(read_data, cheader->getBodyLength());
           cout << "Read " << read_size << endl;
           string auth_class ; 
           Cql3Response::decodeAuthenticate(bf3, auth_class);
           cout << "Auth class " << auth_class << endl;
           map<string, string> credentials;
           credentials["username"] = "nipun";
           credentials["password"] = "abcdef";
           Cql3RequestBody *body = new Cql3Credentials(credentials);
           header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::CREDENTIALS);
           request = new Cql3Request(header, body);
           bf3.rewind();
           request->encode(bf3);
           conn->write(bf3.getRaw(), bf3.position(0));
           read_size = conn->read(read_data, 8);
           bf3.rewind();
           cheader = Cql3Response::decodeResponse(bf3);
           if (cheader->getOpcode() == OpCode::READY) {
               cout << "Authentication is done " 
                   << " body len " << cheader->getBodyLength() << endl;
           } else {
               cout << "Authentication failed \n";
           }
           delete request;

        } else {
            cout << "Some problem \n";
        }

        query = "CREATE KEYSPACE whambam with replication = { 'class' : 'SimpleStrategy', 'replication_factor' : '1' } ";
        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::QUERY);
        body = new Cql3Query(query);
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 8);
        bf3.rewind();
        cheader = Cql3Response::decodeResponse(bf3);
        cout << "I read " << read_size << endl;
        if (cheader->getOpcode() == OpCode::ERROR) {
            cout << "There was some error ";
            cout << "Length of error body " << cheader->getBodyLength() << endl;

            bf3.rewind();
            read_size =  conn->read(read_data, cheader->getBodyLength());
            cout << "Read data " << read_size << endl;
            bf3.rewind();
            Cql3ErrorMsg errorMsg;
            Cql3ErrorDecode::decodeErrorMsg(bf3, errorMsg);
            cout << errorMsg << endl;
        }
        delete request;
        
        query = "USE  whambam;";
        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::QUERY);
        body = new Cql3Query(query);
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 2560);
        delete request;

        query = "CREATE TABLE mydata (mykey text primary key, myval text );";
        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::QUERY);
        body = new Cql3Query(query);
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 8);
        bf3.rewind();
        cheader = Cql3Response::decodeResponse(bf3);
        cout << "I read " << read_size << endl;
        if (cheader->getOpcode() == OpCode::ERROR) {
            cout << "There was some error ";
            cout << "Length of error body " << cheader->getBodyLength() << endl;
            bf3.rewind();
            read_size =  conn->read(read_data, cheader->getBodyLength());
            cout << "Read data " << read_size << endl;
            bf3.rewind();
            Cql3ErrorMsg errorMsg;
            Cql3ErrorDecode::decodeErrorMsg(bf3, errorMsg);
        }
        delete request;

        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::OPTIONS);
        body = new Cql3Options();
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 8);
        bf3.rewind();
        cheader = Cql3Response::decodeResponse(bf3);
        cout << "I read " << read_size << endl;
        if (cheader->getOpcode() == OpCode::SUPPORTED) {
            bf3.rewind();
            read_size =  conn->read(read_data, cheader->getBodyLength());
            cout << "Read data supported " << read_size << endl;
            map<string, list<string> > vals;
            Cql3Response::decodeSupported(bf3, vals); 
            map<string, list<string> > :: iterator it = vals.begin();
            while (it != vals.end()){
                cout << "Printing values for " << it->first << endl;
                list <string> ::iterator it2 = it->second.begin();
                while (it2 != it->second.end()){
                    cout << *it2 ;
                    cout << " ";
                    ++it2;
                }
                cout << "\n";
                ++it;
            }
        }
        delete request;

        int i = 0;
        query = "";
        string key = "";
        string val = "";
        query = "BEGIN BATCH \n";
        char buf[256];
        while (i++ < 5){
           memset(buf, 0, 256);
           snprintf(buf, 256, 
                   "insert into mydata2 (mykey, myval, myval2, myval3, myval4, myval5) values ('pp%d', 'bbb%d', %d, 'ascii%d%d', false, -9.999);", i, i,i, i , i+9);
           query += string(buf);
        }
        query += "\nAPPLY BATCH;";
        
        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::QUERY);
        body = new Cql3Query(query, ConsistencyLevel::ONE);
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 8);
        bf3.rewind();
        cheader = Cql3Response::decodeResponse(bf3);
        if (cheader->getOpcode() == OpCode::ERROR) {
            cout << "There was some error ";
            bf3.rewind();
            read_size =  conn->read(read_data, cheader->getBodyLength());
            bf3.rewind();
            Cql3ErrorMsg errorMsg;
            Cql3ErrorDecode::decodeErrorMsg(bf3, errorMsg);
        } else if (cheader->getOpcode() == OpCode::RESULT) {
            read_size =  conn->read(read_data, cheader->getBodyLength());
            cout << "Read size " << read_size << endl;
            bf3.rewind();
            Cql3Result result;
            Cql3Response::decodeResult(bf3, result);
        }
        delete request;

        query = "select * from mydata2";
        header = new Cql3Header(REQUEST_VERSION, 0 , 0, OpCode::QUERY);
        body = new Cql3Query(query, ConsistencyLevel::ONE);
        request = new Cql3Request(header, body);
        bf3.rewind();
        request->encode(bf3);
        conn->write(bf3.getRaw(), bf3.position(0));
        read_size =  conn->read(read_data, 8);
        bf3.rewind();
        cheader = Cql3Response::decodeResponse(bf3);
        if (cheader->getOpcode() == OpCode::ERROR) {
            cout << "There was some error ";
            bf3.rewind();
            read_size =  conn->read(read_data, cheader->getBodyLength());
            bf3.rewind();
            Cql3ErrorMsg errorMsg;
            Cql3ErrorDecode::decodeErrorMsg(bf3, errorMsg);
        } else if (cheader->getOpcode() == OpCode::RESULT) {
            read_size =  conn->read(read_data, cheader->getBodyLength());
            cout << "Read size " << read_size << endl;
            unlink("a.dmp");
            int fdx = open("a.dmp", O_RDWR | O_CREAT , 0644);
            if (fdx > 0) {
                write(fdx, read_data, read_size);
                close(fdx);
            }
            bf3.rewind();
            Cql3Result result;
            Cql3Response::decodeResult(bf3, result);
            if (result.getResultCode() == ResultCode::RESULT_ROWS) {
                Cql3Rows rows;
                rows.init(bf3, rows, read_size - 1);
                uint32_t rowcount = rows.getRowCount();
                cout << "Rows returned " << rowcount << endl;
                uint32_t a = 0;
                // Columns 
                string col1 = "mykey";
                string col2 = "myval";
                string col3 = "myval2";
                string col4 = "myval3";
                string col5 = "myval4";  

                // values
                string val1 = "";
                string val2 = "";
                int32_t val3 = 0;
                string val4 = "";
                bool  val5 = false;

                Cql3Row *row = 0;
                while (a++ < rowcount){
                    row = rows.getNextRow();
                    if (!row)
                        break;
                    do {
                        if (!row->getString(col1, val1))
                            break;
                        if (!row->getString(col2, val2))
                            break;
                        if (!row->getInt(col3, val3))
                            break;
                        if (!row->getAscii(col4, val4))
                            break;
                        if (!row->getBoolean(col5, val5))
                            break;
                        cout << col1 << "=" << val1 << ", ";
                        cout << col2 << "=" << val2 << ", ";
                        cout << col3 << "=" << val3 << ", ";
                        cout << col4 << "=" << val4 << ", ";
                        cout << col5 << "=" << boolalpha << val5 << endl;
                    } while (false);
                    delete row;
                }
            }
        }
        delete request;

        delete conn;
    } catch (const char *ex) {
        cout << ex << endl;
    }
    return 0;
}
