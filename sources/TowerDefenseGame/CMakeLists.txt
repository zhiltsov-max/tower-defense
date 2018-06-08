cmake_minimum_required(VERSION 3.6)

project(TowerDefense VERSION 0.1.0)

find_package(GameEngine)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Scripts
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules
    )

set(CMAKE_CXX_STANDARD_REQUIRED 14)

include(CTest)
if (BUILD_TESTING)
    find_package(GTest REQUIRED)
    set(PROJECT_TESTS_INSTALL_DIR bin/tests)
    set(PROJECT_TESTS tests)
    add_custom_target(tests) # create aggregating target for unit tests
endif()

include(Components)

add_subdirectory(docs)
add_subdirectory(components)
add_subdirectory(samples)