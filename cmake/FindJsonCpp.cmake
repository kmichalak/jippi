# -*- cmake -*-

# - Find JSONCpp
# Find the JSONCpp includes and library
# This module defines
#  JSONCPP_INCLUDE_DIR, where to find json.h, etc.
#  JSONCPP_LIBRARIES, the libraries needed to use jsoncpp.
#  JSONCPP_FOUND, If false, do not try to use jsoncpp.
#  also defined, but not for general use are
#  JSONCPP_LIBRARY, where to find the jsoncpp library.

find_path(JsonCpp_INCLUDE_DIR "json/json.h"
  PATH_SUFFIXES "jsoncpp"
  DOC "Specify the JsonCpp include directory here")

find_library(JsonCpp_LIBRARY
  NAMES jsoncpp
  PATHS
  DOC "Specify the JsonCpp library here")
set(JsonCpp_INCLUDE_DIRS ${JsonCpp_INCLUDE_DIR})
set(JsonCpp_LIBRARIES "${JsonCpp_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JsonCpp DEFAULT_MSG
  JsonCpp_LIBRARIES JsonCpp_INCLUDE_DIRS)

mark_as_advanced(JsonCpp_INCLUDE_DIR JsonCpp_LIBRARY)