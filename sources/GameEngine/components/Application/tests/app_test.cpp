#include "GameEngine/Utility/debug.h"
#include "GameEngine/Application/basic_application.h"
#include "gtest/gtest.h"


using namespace GE;

class TestApplication :
    public ::testing::Test,
    public TBasicApplication
{
public:
    static const TBasicApplication::TParameters parameters;

    TestApplication() :
        ::testing::Test(),
        TBasicApplication(parameters)
    {}
};

const TBasicApplication::TParameters TestApplication::parameters = [] {
    TBasicApplication::TParameters parameters;
    parameters.window.title = "Test window";
    parameters.window.style = sf::Style::Default;
    parameters.window.width = 200;
    parameters.window.height = 200;
    return parameters;
} ();


TEST_F(TestApplication, initialization) {
    EXPECT_EQ(parameters.window.width, getWindowWidth());
    EXPECT_EQ(parameters.window.height, getWindowHeight());
}

TEST_F(TestApplication, set_title_wokring) {
    EXPECT_NO_THROW(setTitle(TEXT("title 2")));
}

TEST_F(TestApplication, get_time_working) {
    ASSERT_NO_THROW(getTime());
}

TEST_F(TestApplication, get_debug_tools_working) {
    ASSERT_NO_THROW(getDebugTools());
}

TEST_F(TestApplication, get_device_controller_working) {
    ASSERT_NO_THROW(getDeviceController());
}

#if !defined(NO_GUI_APPLICATION)
TEST_F(TestApplication, get_ui_working) {
    ASSERT_NO_THROW(getUI());
}
#endif

TEST_F(TestApplication, debug_subsystem_working) {
    auto& debug = getDebugTools();

    ASSERT_NO_THROW(
        debug.log("Test message", LogMessageImportance::Important));
}


