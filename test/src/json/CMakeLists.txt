project(testjson)

set (TESTS_EXECUTABLE test-json)
set (TEST_SOURCE_DIR ${testjson_SOURCE_DIR})
set (LIB_UNDER_TEST_SOURCE_DIR ${JSON_SRC})
set (LIB_UNDER_TEST ${JSON_PARSER_LIBRARY})

include_directories(${TEST_SOURCE_DIR})

file (
    GLOB TEST_HEADERS
    ${TEST_SOURCE_DIR}/*.hpp
)

file (
    GLOB TEST_SRC
    ${TEST_SOURCE_DIR}/*.cpp
)

add_executable( ${TESTS_EXECUTABLE} ${TEST_SRC} ${LIB_UNDER_TEST_SOURCE_DIR})
target_link_libraries(
    ${TESTS_EXECUTABLE}
    ${GTEST_LIBRARY}
    ${JsonCpp_LIBRARY}
    ${LIB_UNDER_TEST}
)
