# Use g++
CC=g++
CFLAGS=-c -Wall

INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS  = -lcurl

all: jippi

# default:
# 	g++ -o jippi main.cpp

jippi: main.o restclient.o
	$(CC) $(INCLUDE) $(LDFLAGS) $(LDLIBS) main.o restclient.o -o jippi
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
restclient.o:
	$(CC) $(CFLAGS) rest/client/restclient.cpp
	
clean:
	rm -rf *.o jippi