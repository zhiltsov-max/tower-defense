include(Components)
declare_component(GUI)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()