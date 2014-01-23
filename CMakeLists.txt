cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#
# Find CURL, required for all builds
#
find_package(CURL REQUIRED)

#
# Find LibConfig, required for all builds
#
find_package(LibConfig++ REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

include_directories(/usr/local/include)

# set the path to the library folder
link_directories(/usr/local/lib)

# **************************************
# Link the libraries to the executable
# **************************************
link_libraries(curl)
link_libraries(${LIBCONFIG++_LIBRARY})

add_executable(jippi src/config.cpp src/stringutils.cpp src/restclient.cpp main.cpp)

install(TARGETS jippi RUNTIME DESTINATION bin)

add_subdirectory(src)
add_subdirectory(inc)

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
	add_executable(test-all test/runtests.cpp 
				test/src/restclienttest.cpp src/restclient.cpp 
				test/src/stringutilstest.cpp src/stringutils.cpp
				test/src/configtest.cpp src/config.cpp)

	add_test(NAME test-all COMMAND test-all)
endif()
