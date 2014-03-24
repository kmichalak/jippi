project(testjippi)

set (TESTS_EXECUTABLE test-jippi)
set (TEST_SOURCE_DIR ${testjippi_SOURCE_DIR})
set (LIB_UNDER_TEST_SOURCE_DIR ${JSON_SRC})
set (LIB_UNDER_TEST ${JSON_PARSER_LIBRARY})

find_package(GTest REQUIRED)

include_directories(${TEST_SOURCE_DIR})

file (GLOB APP_SRC ${JIPPI_MAIN_SRC_DIR}/jippi/*.cpp)
list(REMOVE_ITEM APP_SRC ${JIPPI_MAIN_SRC_DIR}/jippi/main.cpp)

file (
    GLOB TEST_SRC
    ${TEST_SOURCE_DIR}/*.cpp
)

add_executable( ${TESTS_EXECUTABLE} ${APP_SRC} ${TEST_SRC} ${LIB_UNDER_TEST_SOURCE_DIR})
target_link_libraries(
    ${TESTS_EXECUTABLE}
    ${GTEST_LIBRARY}
    ${JsonCpp_LIBRARY}
    ${LIBCONFIG++_LIBRARY}

    ${JSON_PARSER_LIBRARY}
    ${RESTCLIENT_LIBRARY}
    ${STRINGUTILS_LIBRARY}
)
