project(teststringutils)

set (TESTS_EXECUTABLE test-stringutils)
set (TEST_SOURCE_DIR ${teststringutils_SOURCE_DIR})
set (LIB_UNDER_TEST_SOURCE_DIR ${STRINGUTILS_SRC})
set (LIB_UNDER_TEST ${STRINGUTILS_LIBRARY})

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
