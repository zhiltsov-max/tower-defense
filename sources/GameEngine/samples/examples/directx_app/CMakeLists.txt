set(target directx_app)
set(sources directx_app.cpp)

add_executable(${target} ${sources})
target_link_libraries(${target}
    ${COMPONENT_Infrastructure}
    )
target_include_directories(${target}
    PUBLIC
        ${COMPONENT_Infrastructure_INCLUDE_DIR}
    )

add_dependencies(EXAMPLES_RESOURCES)

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )