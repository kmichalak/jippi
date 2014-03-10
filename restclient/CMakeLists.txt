project(restclient)

#
# Find CURL, required for all builds - HTTP requests support
#
find_package(CURL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/libstringutils
)

file(GLOB RESTCLIENT_HDERS ${restclientt_SOURCE_DIR}/src/*.hpp)
file(GLOB RESTCLIENT_SRC ${restclient_SOURCE_DIR}/src/*.cpp)

add_library(restclient STATIC ${RESTCLIENT_SRC})

target_link_libraries( restclient ${CURL_LIBRARIES} stringutils )


# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
    
    # GTest required to execute unit tests
    find_package(GTest REQUIRED)
    
    set (TESTS_EXECUTABLE test-restclient)
 
    # Test files
    file (
        GLOB LIBRESTCLIENT_TEST_SRC 
        ${restclient_SOURCE_DIR}/test/*.cpp
    )
    
    add_executable(${TESTS_EXECUTABLE} ${RESTCLIENT_SRC} ${LIBRESTCLIENT_TEST_SRC})
    target_link_libraries(
        ${TESTS_EXECUTABLE} 
        ${GTEST_LIBRARY} 
        ${CURL_LIBRARIES} 
        stringutils
    )
    
    #add_test(NAME test-restclient COMMAND test-restclient)
    
endif()
