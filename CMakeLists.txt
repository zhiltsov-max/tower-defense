cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME TowerDefense)
project(${PROJECT_NAME})
set(ROOT_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(TESTING_ENABLED 1)


if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
    add_compile_options(-Og)
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

include_directories(${ROOT_DIR}/Modules)
include_directories(${ROOT_DIR}/include)
include_directories(${ROOT_DIR}/include/lua52)
include_directories(${ROOT_DIR}/include/luapp)
set(LIBRARY_PATH ${LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(Modules)


if(TESTING_ENABLED)
    enable_testing()
    add_subdirectory(Tests)
endif()

message("Config: Build type - " ${CMAKE_BUILD_TYPE})
if(TESTING_ENABLED)
    message("Config: Testing enabled")
endif()
