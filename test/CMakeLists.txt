project(jippitests)

add_subdirectory(include)
add_subdirectory(src)

include_directories(include)

set(JIPPI_TEST_MAIN_HEADERS_DIR ${jippitests_SOURCE_DIR}/include CACHE STRING "Test sources root")
set(JIPPI_TEST_MAIN_SRC_DIR ${jippitests_SOURCE_DIR}/src CACHE STRING "Test headers root")
