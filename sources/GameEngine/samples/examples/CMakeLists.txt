set(EXAMPLES_INSTALL_DIR ${SAMPLES_INSTALL_DIR}/examples)

add_custom_target(EXAMPLES_RESOURCES) # empty target to depend on

add_subdirectory(directx_app)
add_subdirectory(sfml_app)
add_subdirectory(lua_gui_app)
add_subdirectory(lua_interpreter)

install(DIRECTORY resources
    DESTINATION ${EXAMPLES_INSTALL_DIR})
    )