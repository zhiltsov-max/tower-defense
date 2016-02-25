project(Tests)

include_directories(
    include
    include/gtest
)

set(gtest_LIB -lgtest.dll)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "-L${PROJECT_SOURCE_DIR}/lib")
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")


add_executable(core_test core_test.cpp)
target_link_libraries(core_test 
    -L"${LIBRARY_PATH}"
    -lgtest.dll

    td_core_LIB
)
add_test(NAME test_core
    COMMAND core_test
)


add_executable(gui_test gui_test.cpp)
target_link_libraries(gui_test
    ${LIBRARY_PATH}
    -lgtest.dll
    -lglew32
    -lsfml-system
    -lsfml-main
    -lsfml-window
    -lsfml-graphics
    -llua52

    td_core_LIB
    td_gui_LIB
    td_application_core_LIB
)
add_test(NAME test_gui
    COMMAND gui_test
)
