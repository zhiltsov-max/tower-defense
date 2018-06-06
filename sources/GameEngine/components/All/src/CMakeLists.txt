set(sources
    all.cpp
    )

add_library(${CURRENT_COMPONENT} ${sources})
target_include_directories(${CURRENT_COMPONENT}
    PUBLIC
        ${COMPONENT_Utility_INCLUDE_DIR}
        ${COMPONENT_Infrastructure_INCLUDE_DIR}
        ${COMPONENT_ECS_INCLUDE_DIR}
        ${COMPONENT_GUI_INCLUDE_DIR}
        ${COMPONENT_Application_INCLUDE_DIR}
    INTERFACE
        ${${CURRENT_COMPONENT}_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
target_link_libraries(${CURRENT_COMPONENT}
    PUBLIC
        ${COMPONENT_Utility}
        ${COMPONENT_Infrastructure}
        ${COMPONENT_ECS}
        ${COMPONENT_GUI}
        ${COMPONENT_Application}
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