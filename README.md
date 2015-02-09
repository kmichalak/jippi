jippi [![Build Status](https://travis-ci.org/kmichalak/jippi.svg?branch=master)](https://travis-ci.org/kmichalak/jippi)
=====

Jira command line client written in C++

Building:
---------

This is a very shord description of Jippi build procedure

1. Compiler:
-----------

All versions of Jippi are configured for building on Linux desktop computer.
You need gcc compiler for building desktop version or cross gcc compiler
for building package for another platform.

2. Tools:
---------

CMake - usefull tool for build process automation 


3. Libraries:
-------------

Jippi requires:

* LibConfig++ >= 1.4.9 -- library for configuration file parsing.
* CURL, version >= 7.27.0 -- for network libraries integration. 
* JsonCpp, version >= 0.5.0 -- library for JSON parsing.

* GTest, version >= 1.7.0 -- unit tests
 

4. How to build:
----------------

A normal Linux compilation is made in two steps:

    cmake . 
    make 
    
If you need to run unit tests during build -Dbuild_tests=BOOL:ON paramater
to the cmake command:

    cmake . -Dbuild_tests=BOOL:ON
    make 
    

