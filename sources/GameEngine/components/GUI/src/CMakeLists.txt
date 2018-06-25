add_library(${CURRENT_COMPONENT_LIBRARY}
    abstractbutton.cpp
    abstracttextarea.cpp
    abstracttextbox.cpp
    abstractwindow.cpp
    customfont.cpp
    customfonts_cache.cpp
    gui_core.cpp
    gui_lua_binding.cpp
    imagebox.cpp
    messagebox.cpp
    movingtext.cpp
    okdialog.cpp
    pushbutton.cpp
    richtextarea.cpp
    richtextbox.cpp
    signal_defs.cpp
    simpletext.cpp
    simpletextbox.cpp
    transparentwindow.cpp
    uiparent.cpp
    widget.cpp
    widget_event_system.cpp
    widget_signal.cpp
    widget_slot.cpp
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