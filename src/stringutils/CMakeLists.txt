set (STRINGUTILS_LIBRARY "stringutils" CACHE STRING "String Utils Library")

project(${STRINGUTILS_LIBRARY})

file(GLOB STRINGUTILS_HEADERS ${JIPPI_MAIN_HEADERS_DIR}/stringutils/*.hpp)
file(GLOB STRINGUTILS_SRC ${stringutils_SOURCE_DIR}/*.cpp)

add_library(stringutils STATIC ${STRINGUTILS_HEADERS} ${STRINGUTILS_SRC})
