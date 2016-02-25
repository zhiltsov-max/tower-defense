project(TD_Application)

set(application_core_headers 
    application.h 
    debug.h 
    fpscounter.h 
    application_ui.h
)

set(application_core_sources
    application.cpp 
    debug.cpp 
    fpscounter.cpp 
    application_ui.cpp
)

add_library(td_application_core_LIB STATIC 
    ${application_core_headers} ${application_core_sources})
target_link_libraries(td_application_core_LIB
    td_core_LIB
    td_gui_LIB
)
