cmake_minimum_required(VERSION 2.8)

project(jippi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

#
# Find CURL, required for all builds - HTTP requests support
#
#find_package(CURL REQUIRED)

#
# Find LibConfig, required for all builds - configuration support
#
find_package(LibConfig++ REQUIRED)

#
# Find JsonCPP library, required for all build - JSON support
#
find_package(JsonCpp REQUIRED)


include_directories(/usr/local/include)

# Add project includes
include_directories(${jippi_SOURCE_DIR})

include_directories(librest/src)

add_subdirectory(libstringutils)
add_subdirectory(librest)

add_subdirectory(inc)
add_subdirectory(src)

add_executable(
            jippi 
            src/jippi.cpp
            src/jsonparser.cpp
            src/json/assignee.cpp
            src/json/issue.cpp
            src/json/issuetype.cpp
            src/json/project.cpp
            src/json/progress.cpp
            src/json/reporter.cpp
            src/json/votesparser.cpp 
            src/json/priorityparser.cpp
            src/getissueaction.cpp 
            src/argumentshandler.cpp 
            src/config.cpp
            main.cpp
    )

# 
# Link the libraries to the executable
#
target_link_libraries(jippi ${LIBCONFIG++_LIBRARY} ${JsonCpp_LIBRARY} ${CURL_LIBRARIES} restclient stringutils)

install(TARGETS jippi RUNTIME DESTINATION bin)



# **************************************
# Build tests
# **************************************

# cmake -Dbuild_tests=BOOL:ON
if(build_tests)
    find_package(GTest REQUIRED)

    add_subdirectory(test)
    add_subdirectory(test/inc)
    add_subdirectory(test/inc/json)
    add_subdirectory(test/src)
    add_subdirectory(test/src/json)
    
    add_executable(
                test-all 
                test/src/runtests.cpp
                test/src/configtest.cpp                 src/config.cpp
                test/src/json/jsonparsertest.cpp        src/jsonparser.cpp  
                test/src/json/assigneeparsertest.cpp    src/json/assignee.cpp
                test/src/json/issueparsertest.cpp       src/json/issue.cpp  
                test/src/json/issuetypeparsertest.cpp   src/json/issuetype.cpp  
                test/src/json/reporterparsertest.cpp    src/json/reporter.cpp
                test/src/json/votesparsertest.cpp       src/json/votesparser.cpp 
                test/src/json/priorityparsertest.cpp    src/json/priorityparser.cpp
                test/src/json/projectparsertest.cpp     src/json/project.cpp
                test/src/json/progressparsertest.cpp    src/json/progress.cpp
    )

    target_link_libraries(test-all ${GTEST_LIBRARY} ${LIBCONFIG++_LIBRARY} ${JsonCpp_LIBRARY} ${CURL_LIBRARIES} stringutils)
    
    add_test(NAME test-all COMMAND test-all)
endif()
