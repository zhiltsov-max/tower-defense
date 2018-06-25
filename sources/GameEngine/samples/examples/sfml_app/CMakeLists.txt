set(target sfml_app)

add_executable(${target}
    sfml_app.cpp)
target_link_libraries(${target}
    PRIVATE
        ${SFML_LIBRARIES}
    )
target_include_directories(${target}
    PRIVATE
        ${SFML_INCLUDE_DIRS}
    )

add_dependencies(${target} EXAMPLES_RESOURCES)

install(TARGETS ${target}
    DESTINATION ${EXAMPLES_INSTALL_DIR}/${target}
    )