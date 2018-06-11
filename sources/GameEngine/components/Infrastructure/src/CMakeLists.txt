set(sources
    device_controller.cpp
    graphics.cpp
    point.cpp
    window.cpp
    )

set(BACKEND_WINAPI "WINAPI")
set(BACKEND_SFML "SFML")
set(GAMEENGINE_BACKEND_TYPES "${BACKEND_SFML};${BACKEND_WINAPI};" CACHE STRING "Configs" FORCE)

if (NOT DEFINED GAMEENGINE_BACKEND)
    set(GAMEENGINE_BACKEND ${BACKEND_SFML} CACHE STRING "Backend for GameEngine" FORCE)
endif()

if(GAMEENGINE_BACKEND STREQUAL ${BACKEND_SFML})
    set(platform_sources
        ""
        )
    set(sources ${sources} ${platform_sources})
    set(includes ${SFML_INCLUDE_DIRS})
    set(libraries ${SFML_LIBRARIES})
elseif(GAMEENGINE_BACKEND STREQUAL ${BACKEND_WINAPI})
    set(platform_sources
        ""
        )
    set(sources ${sources} ${platform_sources})
    set(includes "")
    set(libraries "")
else()
    message(FATAL_ERROR "Selected unknown Application backend "
        "(variable GAMEENGINE_BACKEND): '${GAMEENGINE_BACKEND}'. "
        "Select one of ${GAMEENGINE_BACKEND_TYPES}.")
endif()

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