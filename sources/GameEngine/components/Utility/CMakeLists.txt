include(Components)
declare_component(Utility)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()