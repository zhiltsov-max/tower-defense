set(target lua_interpreter)

add_executable(${target}
    lua_interpreter.cpp
    )
target_link_libraries(${target}
    PRIVATE
        ${GAME_ENGINE_NAMESPACE}::Utility
    )

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )