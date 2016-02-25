project(Core)


set(core_headers
    checkdef.h
    core.h
    datastructures.h
    defs.h
    devicecontroller.h
    exception.h
    graphics.h
    graphicsdevice.h
    image.h
    io.h
    key_defs.h
    luawrapper.h
    math.h
    myon_datareader.h
    nameddata.h
    point.h
    string.h
)

set(core_sources
    devicecontroller.cpp
    exception.cpp
    graphics.cpp
    graphicsdevice.cpp
    io.cpp
    luawrapper.cpp
    math.cpp
    myon_datareader.cpp
    point.cpp
    string.cpp
)

add_library(td_core_LIB STATIC
    ${core_headers} ${core_sources})
target_link_libraries(td_core_LIB
    -lglew32
    -lsfml-system
    -lsfml-main
    -lsfml-window
    -lsfml-graphics
    -llua52
)
