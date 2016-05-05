project(GameEngine)

set(game_engine_headers
    engine_core.h
    registry.h
    component.h
    component_registry.h
    scene.h
    script_engine.h
    scene_resource.h
    scene_resources.h
    component_systems.h
    component_system.h
    ComponentSystems/component_system_graphics.h
    ComponentSystems/component_system_input.h
    ComponentSystems/component_system_movement.h
    ComponentSystems/component_system_logics.h
    ComponentSystems/component_system_sound.h
    ComponentSystems/component_system_ui.h
    scene_object.h
    scene_object_container.h
    engine_message.h
    engine_messages.h
    game_engine.h
    engine_lua_binding.h
)

set(game_engine_sources
    scene.cpp
    script_engine.cpp
    scene_resource.cpp
    scene_resources.cpp
    component.cpp
    component_system.cpp
    ComponentSystems/component_system_graphics.cpp
    ComponentSystems/component_system_input.cpp
    ComponentSystems/component_system_movement.cpp
    ComponentSystems/component_system_logics.cpp
    ComponentSystems/component_system_sound.cpp
    ComponentSystems/component_system_ui.cpp
    scene_object.cpp
    scene_object_container.cpp
    engine_message.cpp
    engine_messages.cpp
    game_engine.cpp
    component_systems.cpp
)

add_library(td_game_engine_LIB STATIC
    ${game_engine_headers} ${game_engine_sources})
target_link_libraries(td_game_engine_LIB
    td_core_LIB
    td_application_core_LIB
    td_gui_LIB
)
