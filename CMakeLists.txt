cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME TowerDefense)
project(${PROJECT_NAME})
set(ROOT_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile;" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
    add_compile_options(-Og)
elseif(CMAKE_BUILD_TYPE STREQUAL Profile)
    add_compile_options(-g)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wno-reorder
        -Wno-pmf-conversions
    )
elseif(MSVC)
    add_compile_options(
        /Za # disable MS extensions
    )
endif()

add_definitions(-DSFML -DUNICODE)
add_compile_options(
    -std=c++11
    -Wall
)

# Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ROOT_DIR}/cmake/Modules)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${ROOT_DIR}/lib)

if(SFML_INCLUDE_DIR STREQUAL "SFML_INCLUDE_DIR-NOTFOUND" OR NOT SFML_INCLUDE_DIR)
    set(SFML_INCLUDE_DIR "${ROOT_DIR}/include" CACHE STRING "Path to a directory." FORCE)
endif()
find_package(SFML COMPONENTS system window graphics main REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

if(LUA_INCLUDE_DIR STREQUAL "LUA_INCLUDE_DIR-NOTFOUND" OR NOT LUA_INCLUDE_DIR)
    set(LUA_INCLUDE_DIR "${ROOT_DIR}/include/lua52" CACHE STRING "Path to a directory." FORCE)
endif()
find_package(LUA REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

include_directories(${ROOT_DIR}/include/luapp)
include_directories(${ROOT_DIR}/include)
include_directories(${ROOT_DIR}/modules)

add_subdirectory(modules)

# Testing
if(NOT TESTING_ENABLED)
    set(TESTING_ENABLED OFF CACHE BOOL "Enable building of tests." FORCE)
endif()

if(TESTING_ENABLED)
    if(GTEST_INCLUDE_DIR STREQUAL "GTEST_INCLUDE_DIR-NOTFOUND" OR NOT GTEST_INCLUDE_DIR)
        set(GTEST_INCLUDE_DIR "${ROOT_DIR}/include/" CACHE STRING "Path to a directory." FORCE)
    endif()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    enable_testing()
    add_subdirectory(tests)
endif()

message("Config: Build type - " ${CMAKE_BUILD_TYPE})
if(TESTING_ENABLED)
    message("Config: Testing enabled")
else()
    message("Config: Testing disabled")
endif()

message("") # empty string
