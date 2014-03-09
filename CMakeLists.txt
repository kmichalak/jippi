cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

#
# Find LibConfig, required for all builds - configuration support
#
find_package(LibConfig++ REQUIRED)


include_directories(/usr/local/include)

# Add project includes
include_directories(${jippi_SOURCE_DIR})

include_directories(libjson)

add_subdirectory(libstringutils)
add_subdirectory(librest)
add_subdirectory(libjson)

add_subdirectory(inc)
add_subdirectory(src)

file(GLOB JIPPI_SRC ${jippi_SOURCE_DIR}/src/*.cpp)

add_executable(jippi ${JIPPI_SRC})

# 
# Link the libraries to the executable
#
target_link_libraries(jippi ${LIBCONFIG++_LIBRARY} jsonparser restclient)

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
    
    include_directories(test/inc/)
    
    file(GLOB JIPPI_TEST_SRC ${jippi_SOURCE_DIR}/test/src/*.cpp)
    # Remove mapn.cpp from the files list to avoid problem  
    # with multiple definition of `main'.
    list(REMOVE_ITEM JIPPI_SRC ${jippi_SOURCE_DIR}/src/main.cpp)
    
    add_executable( test-all ${JIPPI_TEST_SRC} ${JIPPI_SRC})

    target_link_libraries(test-all ${GTEST_LIBRARY} ${LIBCONFIG++_LIBRARY} jsonparser restclient)
    
    add_test(NAME test-all COMMAND test-all)
endif()
