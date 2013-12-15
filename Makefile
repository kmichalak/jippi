# Use g++
CC=g++
CFLAGS=-c -g -Wall
CXXFLAGS = -std=c++11

INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS  = -lcurl

all: jippi

jippi: main.o restclient.o stringutils.o
	$(CC) $(INCLUDE) $(LDFLAGS) $(CXXFLAGS) $(LDLIBS) main.o restclient.o stringutils.o -o jippi
	
main.o: main.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) main.cpp
	
restclient.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) rest/client/restclient.cpp
	
stringutils.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) utils/string/stringutils.cpp
	
clean:
	rm -rf *.o jippi