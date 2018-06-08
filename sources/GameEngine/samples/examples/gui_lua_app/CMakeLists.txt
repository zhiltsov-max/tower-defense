set(target gui_lua_app)
set(sources gui_lua_app.cpp)

add_executable(${target} ${sources})
target_link_libraries(${target}
    ${COMPONENT_GUI}
    ${COMPONENT_Application}
    )
target_include_directories(${target}
    PUBLIC
        ${COMPONENT_GUI_INCLUDE_DIR}
        ${COMPONENT_Application_INCLUDE_DIR}
    )

add_dependencies(${target} EXAMPLES_RESOURCES)

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )