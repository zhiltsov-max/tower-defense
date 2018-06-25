set(EXAMPLES_INSTALL_DIR ${SAMPLES_INSTALL_DIR}/examples)

add_custom_target(EXAMPLES_RESOURCES) # empty target to depend on

add_subdirectory(sfml_app)
add_subdirectory(gui_lua_app)
add_subdirectory(lua_interpreter)

install(DIRECTORY resources
    DESTINATION ${EXAMPLES_INSTALL_DIR}
    )