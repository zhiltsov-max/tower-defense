project(Tests)

include_directories(
    include
    include/gtest
)

set(gtest_LIB -lgtest.dll)
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")


add_executable(core_test core_test.cpp)
target_link_libraries(core_test 
    -L"${LIBRARY_PATH}"
    -L"${PROJECT_SOURCE_DIR}/lib"
    -lgtest.dll

    td_core_LIB
)
add_test(NAME test_core
    COMMAND core_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(gui_test gui_test.cpp)
target_link_libraries(gui_test
    -L"${LIBRARY_PATH}"
    -L"${PROJECT_SOURCE_DIR}/lib"
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
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(application_test app_test.cpp)
target_link_libraries(application_test
    -L"${LIBRARY_PATH}"
    -L"${PROJECT_SOURCE_DIR}/lib"
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
add_test(NAME test_application
    COMMAND application_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)


add_executable(graphics_test graphics_test.cpp)
target_link_libraries(graphics_test
    -L"${LIBRARY_PATH}"
    -L"${PROJECT_SOURCE_DIR}/lib"
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
add_test(NAME test_graphics
    COMMAND graphics_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
