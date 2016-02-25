cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME TowerDefense)
project(${PROJECT_NAME})
set(ROOT_DIR ${PROJECT_SOURCE_DIR})

if(not ${CMAKE_BUILD_TYPE} ) 
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_definitions(-DSFML -DUNICODE)
add_compile_options(
    -std=c++11
    -Og
    -Wno-reorder
    -Wno-pmf-conversions
    -Wall
)

include_directories(${ROOT_DIR}/Modules)
include_directories(${ROOT_DIR}/include)
include_directories(${ROOT_DIR}/include/lua52)
include_directories(${ROOT_DIR}/include/luapp)
set(LIBRARY_PATH ${LIBRARY_PATH} "-L\"${PROJECT_SOURCE_DIR}/lib\"")

add_subdirectory(Modules)


enable_testing()
add_subdirectory(Tests)
