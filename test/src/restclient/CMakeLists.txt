project(testrestclient)

set (TESTS_EXECUTABLE test-restclient)
set (TEST_SOURCE_DIR ${testrestclient_SOURCE_DIR})
set (LIB_UNDER_TEST_SOURCE_DIR ${RESTCLIENT_SRC})
set (LIB_UNDER_TEST ${RESTCLIENT_LIBRARY})

include_directories(${TEST_SOURCE_DIR})

file (
    GLOB TEST_SRC
    ${TEST_SOURCE_DIR}/*.cpp
)

add_executable( ${TESTS_EXECUTABLE} ${TEST_SRC} ${LIB_UNDER_TEST_SOURCE_DIR})
target_link_libraries(
    ${TESTS_EXECUTABLE}
    ${GTEST_LIBRARY}
    ${LIB_UNDER_TEST}
)
