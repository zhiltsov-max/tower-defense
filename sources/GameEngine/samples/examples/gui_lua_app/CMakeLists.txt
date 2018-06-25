set(target gui_lua_app)

add_executable(${target}
    gui_lua_app.cpp
    )
target_link_libraries(${target}
    PRIVATE
        ${GAME_ENGINE_NAMESPACE}::GUI
        ${GAME_ENGINE_NAMESPACE}::Application
    )

add_dependencies(${target} EXAMPLES_RESOURCES)

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )