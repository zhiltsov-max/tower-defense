set(target sfml_app)
set(sources sfml_app.cpp)

add_executable(${target} ${sources})
target_link_libraries(${target}
    ${SFML_LIBRARIES}
    )
target_include_directories(${target}
    PUBLIC
        ${SFML_INCLUDE_DIRS}
    )

add_dependencies(${target} EXAMPLES_RESOURCES)

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )