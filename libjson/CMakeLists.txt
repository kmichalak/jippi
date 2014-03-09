project(jsonparser)

#
# Find JsonCPP library, required for all build - JSON support
#
find_package(JsonCpp REQUIRED)

file( GLOB JSONPARSER_HEADERS ${jsonparser_SOURCE_DIR}/*.hpp )
file( GLOB JSONPARSER_SRC ${jsonparser_SOURCE_DIR}/*.cpp )

add_library(jsonparser STATIC ${JSONPARSER_SRC})

target_link_libraries(jsonparser ${JsonCpp_LIBRARY})


# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
    
    # GTest required to execute unit tests
    find_package(GTest REQUIRED)
    
    set (TESTS_EXECUTABLE test-jsonparser)
 
    # Test files
    file (
        GLOB JSONPARSER_TEST_SRC 
        ${jsonparser_SOURCE_DIR}/test/*.cpp
    )
    
    add_executable(${TESTS_EXECUTABLE} ${JSONPARSER_SRC} ${JSONPARSER_TEST_SRC})
    target_link_libraries(
        ${TESTS_EXECUTABLE} 
        ${GTEST_LIBRARY} 
        ${JsonCpp_LIBRARY} 
        stringutils
    )
    
endif()
