set(sources
    device_controller.cpp
    graphics.cpp
    point.cpp
    window.cpp
    )

set(platform_sources
    ""
    )
set(sources ${sources} ${platform_sources})
set(includes ${SFML_INCLUDE_DIRS})
set(libraries ${SFML_LIBRARIES})

add_library(${CURRENT_COMPONENT} ${sources})
target_include_directories(${CURRENT_COMPONENT}
    INTERFACE
        ${${CURRENT_COMPONENT}_INCLUDE_DIR}
    PRIVATE
        ${includes}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT}
    PUBLIC
        ${COMPONENT_Utility}
    PRIVATE
        ${libraries}
    )

install(TARGETS ${CURRENT_COMPONENT}
    EXPORT ${PROJECT_NAME}Targets # for downstream dependencies
    RUNTIME DESTINATION bin # binaries
        COMPONENT ${CURRENT_COMPONENT_NAME}
    ARCHIVE DESTINATION lib # static lib
        COMPONENT ${CURRENT_COMPONENT_NAME}
    LIBRARY DESTINATION lib # shared lib
        COMPONENT ${CURRENT_COMPONENT_NAME}
    INCLUDES DESTINATION include # headers
)