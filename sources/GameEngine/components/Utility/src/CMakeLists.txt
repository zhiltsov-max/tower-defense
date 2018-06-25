add_library(${CURRENT_COMPONENT_LIBRARY}
    debug.cpp
    exception.cpp
    lua_wrapper.cpp
    )
target_include_directories(${CURRENT_COMPONENT_LIBRARY}
    PUBLIC
        ${CURRENT_COMPONENT_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT_LIBRARY}
    PUBLIC
        luapp::luapp
        json::json
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