# Script to find out LUAPP library.
#
# The library is header-only and should be compiled with containing project.
#
# Script sets the following variables:
# - LUAPP_FOUND - library search results
# - LUAPP_INCLUDE_DIRS - luapp source directory
# - LUAPP_LIBRARIES - empty value
# - LUAPP_DEFINITIONS - compiler definitions required to use the library
#
# The LUAPP_COMPATIBILITY variable might be set to specify used LUA version.
# The accessible values are "5.1", "5.2" and "5.3"

if (NOT DEFINED LUAPP_COMPATIBILITY)
    set(LUAPP_COMPATIBILITY "5.2")
endif()

if (LUAPP_COMPATIBILITY EQUAL "5.1")
    find_package(LUA 5.1)
    set(LUAPP_DEFINITIONS -DLUAPP_COMPATIBILITY_V51)
elseif(LUAPP_COMPATIBILITY EQUAL "5.2")
    find_package(LUA 5.2)
    set(LUAPP_DEFINITIONS -DLUAPP_COMPATIBILITY_V52)
elseif(LUAPP_COMPATIBILITY EQUAL "5.3")
    find_package(LUA 5.3)
    set(LUAPP_DEFINITIONS -DLUAPP_COMPATIBILITY_V53)
else()
    message(FATAL_ERROR "LUAPP supports only 5.1, 5.2 and 5.3 LUA versions.")
endif()

find_path(LUAPP_INCLUDE_DIR luapp/lua.hpp
    HINTS ${LUAPP_ROOT}
    PATH_SUFFIXES include
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LUAPP
    REQUIRED_VARS LUAPP_INCLUDE_DIR)

set(LUAPP_LIBRARIES ${LUAPP_LIBRARY})
set(LUAPP_INCLUDE_DIRS ${LUAPP_INCLUDE_DIR})