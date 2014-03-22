set (RESTCLIENT_LIBRARY "restclient" CACHE STRING "Rest Client Library")

project(${RESTCLIENT_LIBRARY})

# Find CURL, required for all builds - HTTP requests support
find_package(CURL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/libstringutils
)

file(
    GLOB RESTCLIENT_HEADERS
    file(GLOB STRINGUTILS_HEADERS ${JIPPI_MAIN_HEADERS_DIR}/restclient/*.hpp)
)

file(
    GLOB RESTCLIENT_SRC
    ${restclient_SOURCE_DIR}/src/*.cpp
)

add_library(restclient STATIC ${RESTCLIENT_HEADERS} ${RESTCLIENT_SRC})

target_link_libraries( restclient ${CURL_LIBRARIES} stringutils )

