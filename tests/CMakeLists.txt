project(Tests)
include_directories(include)
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")


add_executable(core_test core_test.cpp)
target_link_libraries(core_test 
    ${GTEST_LIBRARIES}    
    td_core_LIB
)
add_test(NAME test_core
    COMMAND core_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(gui_test gui_test.cpp)
target_link_libraries(gui_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
)
add_test(NAME test_gui
    COMMAND gui_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(application_test app_test.cpp)
target_link_libraries(application_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
)
add_test(NAME test_application
    COMMAND application_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(graphics_test graphics_test.cpp)
target_link_libraries(graphics_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
)
add_test(NAME test_graphics
    COMMAND graphics_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

add_executable(game_engine_test game_engine_test.cpp)
target_link_libraries(game_engine_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
    td_game_engine_LIB
)
add_test(NAME test_game_engine
    COMMAND game_engine_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

add_executable(td_level_test td_level_test.cpp
    ../modules/Game/Components/components_list.h
    ../modules/Game/Components/game_objects_info.h
    ../modules/Game/Level/level.h
    ../modules/Game/Level/level_clock.h
    ../modules/Game/Level/level_info_loader.h
    ../modules/Game/Level/level_info_loader_impl.h
    ../modules/Game/Level/level_lua_binding.h
    ../modules/Game/Level/level_scene.h
    ../modules/Game/Components/components_list.cpp
    ../modules/Game/Level/level.cpp
    ../modules/Game/Level/level_clock.cpp
    ../modules/Game/Level/level_info_loader.cpp
    ../modules/Game/Level/level_lua_binding.cpp
    ../modules/Game/Level/level_scene.cpp
)
target_link_libraries(td_level_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
    td_game_engine_LIB
)
add_test(NAME test_td_level
    COMMAND td_level_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

add_executable(td_map_components_test td_map_components_test.cpp
    ../modules/Game/Components/components_list.h
    ../modules/Game/Components/game_objects_info.h
    ../modules/Game/Level/level.h
    ../modules/Game/Level/level_clock.h
    ../modules/Game/Level/level_info_loader.h
    ../modules/Game/Level/level_info_loader_impl.h
    ../modules/Game/Level/level_lua_binding.h
    ../modules/Game/Level/level_scene.h
    ../modules/Game/Components/components_list.cpp
    ../modules/Game/Level/level.cpp
    ../modules/Game/Level/level_clock.cpp
    ../modules/Game/Level/level_info_loader.cpp
    ../modules/Game/Level/level_lua_binding.cpp
    ../modules/Game/Level/level_scene.cpp
    ../modules/Game/Map/level_node_map.h
    ../modules/Game/Map/level_passability_map.h
    ../modules/Game/Map/level_tile_map.h
    ../modules/Game/Map/level_tile_map_tileset.h
    ../modules/Game/Map/level_tile_map_tileset_registry.h
    ../modules/Game/Map/level_node_map.cpp
    ../modules/Game/Map/level_passability_map.cpp
    ../modules/Game/Map/level_tile_map.cpp
    ../modules/Game/Map/level_tile_map_tileset_registry.cpp
)
target_link_libraries(td_map_components_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
    td_game_engine_LIB
)
add_test(NAME test_td_map_components
    COMMAND td_map_components_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

add_executable(gui_application_test examples/gui_app_test.cpp)
target_link_libraries(gui_application_test
    ${GTEST_LIBRARIES}
    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
)
