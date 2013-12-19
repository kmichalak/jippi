# Use g++
CC=g++
CFLAGS=-c -g -Wall
CXXFLAGS = -std=c++11

INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS  = -lcurl

TEST_LDFLAGS = -L/usr/local/gtest-1.6.0/lib
TEST_LDLIBS = -lgtest

all: jippi

jippi: main.o restclient.o stringutils.o
	$(CC) $(INCLUDE) $(LDFLAGS) $(CXXFLAGS) $(LDLIBS) main.o restclient.o stringutils.o -o jippi
	
main.o: main.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) main.cpp
	
restclient.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) src/rest/client/restclient.cpp
	
stringutils.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) src/utils/string/stringutils.cpp
	
	
	
	
tests: runtests.o stringutilstest.o stringutils.o
	$(CC) $(INCLUDE) $(CXXFLAGS) $(TEST_LDFLAGS) $(TEST_LDLIBS) runtests.o stringutilstest.o stringutils.o -o test-all 
	
runtests.o: test/runtests.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) test/runtests.cpp
	
stringutilstest.o: 
	$(CC) $(CFLAGS) $(CXXFLAGS) test/utils/string/stringutilstest.cpp
	
	
	
clean:
	rm -rf *.o jippi test-all