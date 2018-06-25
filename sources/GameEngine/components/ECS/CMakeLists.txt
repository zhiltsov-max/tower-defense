include(Components)
declare_component(ECS)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()