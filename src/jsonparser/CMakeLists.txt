set (JSON_PARSER_LIBRARY "jsonparser" CACHE STRING "JSON Parser Library")

project(${JSON_PARSER_LIBRARY})

# Find JsonCPP library, required for all build - JSON support
find_package(JsonCpp REQUIRED)

file(
    GLOB JSONPARSER_HEADERS
    ${JIPPI_MAIN_HEADERS_DIR}/${JSON_PARSER_LIBRARY}/*.hpp
)

file(
    GLOB JSONPARSER_SRC
    ${jsonparser_SOURCE_DIR}/*.cpp
)

add_library(
    ${JSON_PARSER_LIBRARY}
    STATIC ${JSONPARSER_HEADERS}
    ${JSONPARSER_SRC}
    ../../include/jsonparser/componentsparser.hpp
    )

target_link_libraries(${JSON_PARSER_LIBRARY} ${JsonCpp_LIBRARY})
