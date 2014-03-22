set (JSON_PARSER_LIBRARY "jsonparser" CACHE STRING "JSON Parser Library")

project(${JSON_PARSER_LIBRARY})

# Find JsonCPP library, required for all build - JSON support
find_package(JsonCpp REQUIRED)

file( GLOB JSONPARSER_HEADERS ${JIPPI_MAIN_HEADERS_DIR}/json/*.hpp )
file( GLOB JSONPARSER_SRC ${jsonparser_SOURCE_DIR}/*.cpp )

add_library(jsonparser STATIC ${JSONPARSER_HEADERS} ${JSONPARSER_SRC})

target_link_libraries(jsonparser ${JsonCpp_LIBRARY})
