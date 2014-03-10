cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

set(JIPPI_BIN_DIR ${PROJECT_BINARY_DIR}/bin)
set(JIPPI_LIB_DIR ${JIPPI_BIN_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JIPPI_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${JIPPI_LIB_DIR})

set(EXECUTABLE_OUTPUT_PATH ${JIPPI_BIN_DIR})

set(JIPPI_MAIN_SRC_DIR ${jippi_SOURCE_DIR}/jippi)

#
# Find LibConfig, required for all builds - configuration support
#
find_package(LibConfig++ REQUIRED)

# Add project includes
include_directories(
    /usr/local/include
    ${jippi_SOURCE_DIR} 
    ${jippi_SOURCE_DIR}/libjson
)

add_subdirectory(libstringutils)
add_subdirectory(librest)
add_subdirectory(libjson)
add_subdirectory(jippi)


file(GLOB JIPPI_SRC ${JIPPI_MAIN_SRC_DIR}/*.cpp)

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

    #GTest required to execute unit tests
    find_package(GTest REQUIRED)

    add_subdirectory(test)
    add_subdirectory(test/inc)
    add_subdirectory(test/src)
    
    include_directories(test/inc/)
    
    set (TESTS_EXECUTABLE test-jippi)
    
    file (
        GLOB JIPPI_TEST_SRC 
        ${jippi_SOURCE_DIR}/test/src/*.cpp
    )
    
    # Remove mapn.cpp from the files list to avoid problem  
    # with multiple definition of `main'.
    list(REMOVE_ITEM JIPPI_SRC ${JIPPI_MAIN_SRC_DIR}/main.cpp)
    
    add_executable( ${TESTS_EXECUTABLE} ${JIPPI_TEST_SRC} ${JIPPI_SRC})
    target_link_libraries(
        ${TESTS_EXECUTABLE} 
        ${GTEST_LIBRARY} 
        ${LIBCONFIG++_LIBRARY} 
        jsonparser 
        restclient
    )
    
endif()
