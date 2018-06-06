function(declare_component component_name)
    if (NOT component_name)
        message(FATAL_ERROR "Expected component name as first function parameter.")
    endif()
    set(component_base_dir ${PROJECT_SOURCE_DIR}/components/${component_name})
    set(component_library ${PROJECT_NAME}_${component_name})
    set(COMPONENT_${component_name}_BASE_DIR ${component_base_dir} PARENT_SCOPE)
    set(COMPONENT_${component_name}_INCLUDE_DIR
        $<BUILD_INTERFACE:${component_base_dir}/include> # use absolute path when building
        $<INSTALL_INTERFACE:include> # use relative path when installing
        PARENT_SCOPE)
    set(COMPONENT_${component_name}_SOURCE_DIR ${component_base_dir}/src PARENT_SCOPE)
    set(COMPONENT_${component_name} ${component_library} PARENT_SCOPE)
    set(COMPONENT_${component_name}_LIBRARY ${component_library} PARENT_SCOPE)
endfunction()

function(add_component_unit_tests CURRENT_COMPONENT_NAME)
    # Required variables:
    # - PROJECT_TESTS_INSTALL_DIR - path to the project tests install dir
    # - PROJECT_TESTS - target containing all project tests
    # Should be used from component tests directory.

    set(unit_tests_install_dir ${PROJECT_TESTS_INSTALL_DIR}/${CURRENT_COMPONENT_NAME})

    # Find C/C++ tests
    file(GLOB test_files
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cxx *.cpp *.c
        )

    # Iterate over all the tests found.
    # For each test declare an executable and add it to the CTest tests list.
    set(CURRENT_COMPONENT_UNIT_TESTS "")
    foreach(file_name ${test_files})
        get_filename_component(test_name ${file_name} NAME_WE)
        set(test_name ${CURRENT_COMPONENT_NAME}_${test_name})
        add_executable(${test_name} ${file_name})
        target_link_libraries(${test_name}
            ${CURRENT_COMPONENT}
            gtest
            )
        target_include_directories(${test_name}
            ${CURRENT_COMPONENT_INCLUDE_DIR}
            ${CURRENT_COMPONENT_SOURCE_DIR}
            ${GTEST_INCLUDE_DIRS}
            )
        add_test(NAME ${test_name} COMMAND ${test_name})
        set(CURRENT_COMPONENT_UNIT_TESTS ${CURRENT_COMPONENT_UNIT_TESTS} ${test_name})
    endforeach(file_name)

    install(TARGETS ${CURRENT_COMPONENT_UNIT_TESTS}
        DESTINATION ${unit_tests_install_dir}
    )

    add_custom_target(${CURRENT_COMPONENT_NAME}_unit_tests
        DEPENDS ${CURRENT_COMPONENT_UNIT_TESTS}
        )

    # Add current component unit tests to project tests
    add_dependencies(${PROJECT_TESTS} ${CURRENT_COMPONENT_NAME}_unit_tests)
endfunction()