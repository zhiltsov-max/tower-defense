set(sources
    ComponentSystems/component_system_graphics.cpp
    ComponentSystems/component_system_logics.cpp
    ComponentSystems/component_system_movement.cpp
    ComponentSystems/component_system_sound.cpp
    ComponentSystems/component_system_ui.cpp
    component.cpp
    component_system.cpp
    component_systems_manager.cpp
    engine_message.cpp
    engine_messages.cpp
    game_engine.cpp
    message_system.cpp
    scene.cpp
    scene_component_manager.cpp
    scene_object.cpp
    scene_object_manager.cpp
    scene_resource.cpp
    scene_resources.cpp
    script_engine.cpp
    )

add_library(${CURRENT_COMPONENT} ${sources})
target_include_directories(${CURRENT_COMPONENT}
    PUBLIC
        ${COMPONENT_Utility_INCLUDE_DIR}
        ${COMPONENT_GUI_INCLUDE_DIR}
    INTERFACE
        ${${CURRENT_COMPONENT}_INCLUDE_DIR}
    PRIVATE
        ${COMPONENT_Infrastructure_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT}
    PUBLIC
        ${COMPONENT_Utility}
        ${COMPONENT_GUI}
    PRIVATE
        ${COMPONENT_Infrastructure}
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