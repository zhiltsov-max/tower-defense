project(Application_core)

set(application_core_headers 
    application.h 
    application_ui.h
    debug.h
)

set(application_core_sources
    application.cpp 
    application_ui.cpp
    debug.cpp
)

add_library(td_application_core_LIB STATIC
    ${application_core_headers} ${application_core_sources})
target_link_libraries(td_application_core_LIB
    td_core_LIB
    td_gui_LIB
)
