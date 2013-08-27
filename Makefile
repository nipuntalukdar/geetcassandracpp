CPPFLAGS :=  -W -Wall -Werror -pedantic-errors -fPIC -std=gnu++0x -I . -I /usr/local/include
CQLINCLUDE = protocol/cql/headers
CQLCPP = protocol/cql/cpp
CQL_CPP_FILES := $(wildcard ${CQLCPP}/*.cpp)
CQL_CPP_OBJS := $(CQL_CPP_FILES:.cpp=.o)
TESTCPP = test
TESTCPP_FILES := $(wildcard ${TESTCPP}/*.cpp)
TEST_OBJS := $(TESTCPP_FILES:.cpp=.o) 
CQL_CPP_OBJS := $(CQL_CPP_FILES:.cpp=.o)
LD_FLAGS := -L /usr/local/lib -lboost_system
%.o : %.cpp
	g++ $(CPPFLAGS) -I${CQLINCLUDE} -g -c $< -o  $@
SHARED_LIB = libgeetcasscql.so
TESTBIN = testout
${SHARED_LIB} : ${CQL_CPP_OBJS}
	g++ -shared -fPIC -o ${SHARED_LIB} ${CQL_CPP_OBJS}
${TESTBIN}: ${SHARED_LIB} ${TEST_OBJS}
	g++ -o ${TESTBIN} ${TEST_OBJS} -L. -lgeetcasscql ${LD_FLAGS}
all: ${SHARED_LIB} ${TESTBIN} 
clean:
	rm -f ${CQL_CPP_OBJS} ${SHARED_LIB} ${TESTBIN} ${TEST_OBJS}
