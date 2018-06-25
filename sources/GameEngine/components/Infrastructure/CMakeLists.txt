include(Components)
declare_component(Infrastructure)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()