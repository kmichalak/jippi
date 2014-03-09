project(stringutils)

add_subdirectory(test)

file(GLOB STRINGUTILS_HDERS ${stringutils_SOURCE_DIR}/*.hpp)
file(GLOB STRINGUTILS_SRC ${stringutils_SOURCE_DIR}/*.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_library(stringutils STATIC ${STRINGUTILS_SRC})


# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
    
    # GTest required to execute unit tests
    find_package(GTest REQUIRED)
    
    set (TESTS_EXECUTABLE test-stringutils)
 
    # Test files
    file (
        GLOB STRINGUTILS_TEST_SRC 
        ${stringutils_SOURCE_DIR}/test/*.cpp
    )
    
    add_executable(${TESTS_EXECUTABLE} ${RESTCLIENT_SRC} ${STRINGUTILS_TEST_SRC})
    target_link_libraries(${TESTS_EXECUTABLE} ${GTEST_LIBRARY} stringutils)
    
endif()