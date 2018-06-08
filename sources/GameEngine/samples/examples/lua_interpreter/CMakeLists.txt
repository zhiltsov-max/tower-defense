set(target lua_interpreter)
set(sources lua_interpreter.cpp)

add_executable(${target} ${sources})
target_link_libraries(${target}
    ${COMPONENT_Utility}
    )
target_include_directories(${target}
    PUBLIC
        ${COMPONENT_Utility_INCLUDE_DIR}
    )

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )