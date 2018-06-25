include(Components)
declare_component(Application)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()