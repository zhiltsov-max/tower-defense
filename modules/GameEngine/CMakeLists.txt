project(GameEngine)

set(game_engine_headers
    component.h
    component_registry.h
    component_system.h
    component_systems_manager.h
    ComponentSystems/component_system_graphics.h
    ComponentSystems/component_system_logics.h
    ComponentSystems/component_system_movement.h
    ComponentSystems/component_system_sound.h
    ComponentSystems/component_system_ui.h
    engine_core.h
    engine_lua_binding.h
    engine_message.h
    engine_messages.h
    game_engine.h
    game_engine_context.h
    registry.h
    scene.h
    scene_component_manager.h
    scene_object.h
    scene_object_container.h
    scene_resource.h
    scene_resources.h
    script_engine.h
)

set(game_engine_sources
    component.cpp
    component_system.cpp
    component_systems_manager.cpp
    ComponentSystems/component_system_graphics.cpp
    ComponentSystems/component_system_logics.cpp
    ComponentSystems/component_system_movement.cpp
    ComponentSystems/component_system_sound.cpp
    ComponentSystems/component_system_ui.cpp
    engine_message.cpp
    engine_messages.cpp
    game_engine.cpp
    scene.cpp
    scene_component_manager.cpp
    scene_object.cpp
    scene_object_container.cpp
    scene_resource.cpp
    scene_resources.cpp
    script_engine.cpp
)

add_library(td_game_engine_LIB STATIC
    ${game_engine_headers} ${game_engine_sources})
target_link_libraries(td_game_engine_LIB
    td_core_LIB
    td_application_core_LIB
    td_gui_LIB
)
