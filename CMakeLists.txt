cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

set(JIPPI_BIN_DIR ${PROJECT_BINARY_DIR}/bin)
set(JIPPI_LIB_DIR ${JIPPI_BIN_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JIPPI_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${JIPPI_LIB_DIR})

set(EXECUTABLE_OUTPUT_PATH ${JIPPI_BIN_DIR})

set(JIPPI_MAIN_HEADERS_DIR ${jippi_SOURCE_DIR}/include CACHE STRING "Sources root")
set(JIPPI_MAIN_SRC_DIR ${jippi_SOURCE_DIR}/src CACHE STRING "Headers root")

#
# Find LibConfig, required for all builds - configuration support
#
find_package(LibConfig++ REQUIRED)

# Add project includes
include_directories(
    /usr/local/include
    ${jippi_SOURCE_DIR}
    ${jippi_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(src/jippi)
add_subdirectory(src/json)
add_subdirectory(src/restclient)
add_subdirectory(src/stringutils)

file(GLOB JIPPI_HEADERS ${JIPPI_MAIN_HEADERS_DIR}/jippi/*.hpp)
file(GLOB JIPPI_SRC ${JIPPI_MAIN_SRC_DIR}/jippi/*.cpp)

add_executable(jippi ${JIPPI_HEADERS} ${JIPPI_SRC})

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

    add_subdirectory(test)

endif()
