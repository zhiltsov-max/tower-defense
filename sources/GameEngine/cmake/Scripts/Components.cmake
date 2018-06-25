macro(declare_component component_name)
    #
    # Generic macro to define variables with component structure.
    #
    # Parameters:
    # - component_name
    #
    # Results:
    # - CURRENT_COMPONENT_NAME
    # - CURRENT_COMPONENT_INCLUDE_DIR
    # - CURRENT_COMPONENT_LIBRARY
    # - CURRENT_COMPONENT_SOURCE_DIR
    #

    set(CURRENT_COMPONENT_NAME ${component_name})
    set(CURRENT_COMPONENT_INCLUDE_DIR
            # Make component relocatable by specifying include  paths.
            # Include path used during the component or project build.
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

            # Include path used during component install. This path
            # is relative to install dir.
            $<INSTALL_INTERFACE:include>
        )
    set(CURRENT_COMPONENT_LIBRARY ${CURRENT_COMPONENT_NAME})
    set(CURRENT_COMPONENT_SOURCE_DIR src)
endmacro()

function(add_component_unit_tests CURRENT_COMPONENT_NAME)
    #
    # Generic function to create unit tests target for component.
    # Should be used from component tests directory.
    #
    # Required variables:
    # - PROJECT_TESTS_INSTALL_DIR - path to the project tests install dir
    # - PROJECT_TESTS - target containing all project tests
    # - CURRENT_COMPONENT_NAME
    # - CURRENT_COMPONENT_INCLUDE_DIR
    # - CURRENT_COMPONENT_SOURCE_DIR
    # - CURRENT_COMPONENT_LIBRARY
    #
    # Results:
    # - A single target with all the component unit-tests.
    #

    # Find C/C++ tests
    file(GLOB test_files
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            *.cxx *.cpp *.c
        )

    set(target ${CURRENT_COMPONENT_NAME}_unit_tests)
    add_executable(${target} ${test_files})
    target_link_libraries(${target}
        PRIVATE
            ${CURRENT_COMPONENT_LIBRARY}
            gtest
        )
    target_include_directories(${target}
        PRIVATE
            ${CURRENT_COMPONENT_INCLUDE_DIR}
            ${CURRENT_COMPONENT_SOURCE_DIR}
            ${GTEST_INCLUDE_DIRS}
        )
    add_test(NAME ${target} COMMAND ${target})

    install(TARGETS ${target}
        DESTINATION
            ${PROJECT_TESTS_INSTALL_DIR}/${CURRENT_COMPONENT_NAME}
    )

    add_dependencies(${PROJECT_TESTS} ${target})
endfunction()