# Script to find out JSON library.
#
# The library is header-only and should be compiled with containing project.
#
# Script sets the following variables:
# - JSON_FOUND - library search results
# - JSON_INCLUDE_DIRS - JSON source directory
# - JSON_LIBRARIES - empty value
# - JSON_DEFINITIONS - compiler definitions required to use the library
#

find_path(JSON_INCLUDE_DIR json.hpp
    HINTS ${JSON_ROOT}
    PATH_SUFFIXES include
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSON
    REQUIRED_VARS JSON_INCLUDE_DIR)

set(JSON_LIBRARIES ${JSON_LIBRARY})
set(JSON_INCLUDE_DIRS ${JSON_INCLUDE_DIR})