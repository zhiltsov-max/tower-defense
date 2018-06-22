# General CMakeLists for TowerDefense project.

cmake_minimum_required(VERSION 3.6)

project(TowerDefense)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Scripts
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "Configs" FORCE)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib")

# Third-party libraries setup
set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

# - SFML
if (NOT DEFINED ${SFML_ROOT} OR ${SFML_ROOT} STREQUAL "SFML_ROOT-NOTFOUND")
    set(SFML_ROOT ${THIRDPARTY_DIR}/SFML CACHE STRING "Path to a directory." FORCE)
endif()
find_package(SFML COMPONENTS system window graphics main REQUIRED)

# - LUA
if (NOT DEFINED ENV{LUA_DIR})
    set(ENV{LUA_DIR} ${THIRDPARTY_DIR}/lua-5.3)
endif()
find_package(LUA 5.3 REQUIRED)

# - LUAPP
if (NOT DEFINED LUAPP_ROOT OR LUAPP_ROOT STREQUAL "LUAPP_ROOT-NOTFOUND")
    set(LUAPP_ROOT ${THIRDPARTY_DIR}/luapp CACHE STRING "Path to a directory." FORCE)
endif()
set(LUAPP_COMPATIBILITY 5.3)
find_package(LUAPP REQUIRED)

# - JSON
if (NOT DEFINED JSON_ROOT OR JSON_ROOT STREQUAL "JSON_ROOT-NOTFOUND")
    set(JSON_ROOT ${THIRDPARTY_DIR}/json CACHE STRING "Path to a directory." FORCE)
endif()
find_package(JSON REQUIRED)

# - Threads
find_package(Threads REQUIRED)

# - GTest
include(CTest)
if (BUILD_TESTING)
    if (NOT DEFINED GTEST_ROOT OR GTEST_ROOT STREQUAL "GTEST_ROOT-NOTFOUND")
        set(GTEST_ROOT ${THIRDPARTY_DIR}/gtest CACHE STRING "Path to a directory." FORCE)
    endif()
    find_package(GTest REQUIRED)
endif()


# Compiler flags and definitions setup
if (CMAKE_CXX_COMPILER_ID EQUAL "MINGW")
    add_compile_options(
        -Wall -Wextra # set high level of error-checking
        )
    add_definitions(
        -D_UNICODE -DUNICODE # enable Unicode in Win builds
        )
elseif(MSVC)
    add_compile_options(
        /W4 # set high level of error-checking
        /Za # disable MS extensions
        )
    add_definitions(
        /D_UNICODE /DUNICODE # enable Unicode in Win builds
        )
endif()


set(CMAKE_CXX_STANDARD_REQUIRED 14)


add_subdirectory(sources)

# Show build info
message(" ")
message("==== BUILD SUMMARY ====")
message("-- General --")
message("Config: Build type - ${CMAKE_BUILD_TYPE}")
if (BUILD_TESTING)
    message("Config: Testing enabled")
else()
    message("Config: Testing disabled")
endif()
message("Install dir: ${CMAKE_INSTALL_PREFIX}")
message("-- Libraries --")
message("SFML: ${SFML_INCLUDE_DIR}")
message("LUA: ${LUA_INCLUDE_DIR}")
message("LUAPP: ${LUAPP_INCLUDE_DIR}")
message("GTest: ${GTEST_INCLUDE_DIR}")
message("-- Engine --")
message(" ") # empty string
