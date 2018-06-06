set(sources
    debug.cpp
    exception.cpp
    lua_wrapper.cpp
    math.cpp
    myon_datareader.cpp
    point.cpp
    string.cpp
    )

add_library(${CURRENT_COMPONENT} ${sources})
target_include_directories(${CURRENT_COMPONENT}
    PUBLIC
        $<BUILD_INTERFACE:${LUA_INCLUDE_DIRS}> $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${LUAPP_INCLUDE_DIRS}> $<INSTALL_INTERFACE:include>
    INTERFACE
        ${${CURRENT_COMPONENT}_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT}
    PUBLIC
        ${LUA_LIBRARIES}
    )
target_compile_definitions(${CURRENT_COMPONENT}
    PUBLIC
        ${LUAPP_DEFINITIONS}
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

# add rules for dependencies
install(DIRECTORY
        ${LUA_INCLUDE_DIRS}
        ${LUAPP_INCLUDE_DIRS}
    DESTINATION include
    COMPONENT ${CURRENT_COMPONENT_NAME}
    )