add_library(${CURRENT_COMPONENT_LIBRARY}
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
target_include_directories(${CURRENT_COMPONENT_LIBRARY}
    PUBLIC
        ${CURRENT_COMPONENT_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT_LIBRARY}
    PUBLIC
        ${GAME_ENGINE_NAMESPACE}::Utility
        ${GAME_ENGINE_NAMESPACE}::GUI
    PRIVATE
        ${GAME_ENGINE_NAMESPACE}::Infrastructure
    )

install(TARGETS ${CURRENT_COMPONENT_LIBRARY}
    EXPORT ${PROJECT_NAME}Targets # for downstream dependencies
    RUNTIME DESTINATION bin # binaries
        COMPONENT ${CURRENT_COMPONENT_NAME}
    ARCHIVE DESTINATION lib # static lib
        COMPONENT ${CURRENT_COMPONENT_NAME}
    LIBRARY DESTINATION lib # shared lib
        COMPONENT ${CURRENT_COMPONENT_NAME}
    INCLUDES DESTINATION include # headers
)

add_library(${GAME_ENGINE_NAMESPACE}::${CURRENT_COMPONENT_NAME}
    ALIAS
        ${CURRENT_COMPONENT_LIBRARY})