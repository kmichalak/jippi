cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

#
# Find CURL, required for all builds - HTTP requests support
#
find_package(CURL REQUIRED)

#
# Find LibConfig, required for all builds - configuration support
#
find_package(LibConfig++ REQUIRED)

#
# Find JsonCPP library, required for all build - JSON support
#
find_package(JsonCpp REQUIRED)


include_directories(/usr/local/include)

# Add project includes
include_directories(${jippi_SOURCE_DIR})

# set the path to the library folder
link_directories(/usr/local/lib)

# **************************************
# Link the libraries to the executable
# **************************************
link_libraries(curl)
link_libraries(${LIBCONFIG++_LIBRARY})
link_libraries(${JsonCpp_LIBRARY})

add_subdirectory(src)
add_subdirectory(inc)
                     
add_executable(jippi src/jippi.cpp
		     src/jsonparser.cpp
		     src/getissueaction.cpp 
		     src/argumentshandler.cpp 
		     src/config.cpp 
		     src/stringutils.cpp 
		     src/restclient.cpp 
		     main.cpp)

install(TARGETS jippi RUNTIME DESTINATION bin)



# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
	find_package(GTest REQUIRED)
	
	add_subdirectory(test)
	add_subdirectory(test/inc)
	add_subdirectory(test/src)
	
	link_libraries(gtest)
	link_libraries(${JsonCpp_LIBRARY})
	add_executable(test-all test/src/runtests.cpp
				
				test/src/restclienttest.cpp 	src/restclient.cpp
				test/src/stringutilstest.cpp 	src/stringutils.cpp
				test/src/configtest.cpp 	src/config.cpp
				test/src/jsonparsertest.cpp 	src/jsonparser.cpp
				test/src/assigneeparsertest.cpp
				test/src/projectparsertest.cpp)

	add_test(NAME test-all COMMAND test-all)
endif()
