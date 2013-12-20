cmake_minimum_required(VERSION 2.8)

project(jippi)

#
# Find CURL, required for all builds
#
find_package(CURL REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

include_directories(/usr/local/include)

# set the path to the library folder
link_directories(/usr/local/lib)

# **************************************
# Link the libraries to the executable
# **************************************
link_libraries(curl)

add_executable(jippi src/utils/string/stringutils.cpp src/rest/client/restclient.cpp main.cpp)

install(TARGETS jippi RUNTIME DESTINATION bin)

add_subdirectory(src)

# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
	find_package(GTest REQUIRED)
	add_subdirectory(test)
	add_subdirectory(test/rest)
	
	link_libraries(gtest)
	add_executable(test-all test/rest/client/restclienttest.cpp test/runtests.cpp test/utils/string/stringutilstest.cpp src/utils/string/stringutils.cpp)

	add_test(NAME test-all COMMAND test-all)
endif()
	
