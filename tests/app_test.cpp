#include "Application/application.h"
#include "Application/debug.h"
#include "gtest.h"



class TestApplication :
    public ::testing::Test,
    public TApplication
{
public:
    static const TApplicationInfo info;

    TestApplication() :
        ::testing::Test(),
        TApplication(info)
    {}
};

const TApplicationInfo TestApplication::info = [] {
    TApplicationInfo info;
    info.appTitle = TEXT("TEST");
    info.style = sf::Style::Default;
    info.windowWidth = 200;
    info.windowHeight = 200;
    return info;
} ();


TEST_F(TestApplication, initialization) {
    EXPECT_EQ(info.windowWidth, getWindowWidth());
    EXPECT_EQ(info.windowHeight, getWindowHeight());
}

TEST_F(TestApplication, title) {
    EXPECT_NO_THROW(setTitle(TEXT("title 2")));
}

TEST_F(TestApplication, subsystems) {
    EXPECT_NO_THROW(getTime());
    EXPECT_NO_THROW(getDebugTools());
    EXPECT_NO_THROW(getDeviceController());

#if !defined(NO_GUI_APPLICATION)
    EXPECT_NO_THROW(getUI());
#endif
}

TEST_F(TestApplication, debug_subsystem) {
    auto& debug = getDebugTools();
    EXPECT_NO_THROW(
        debug.log("Test message", LogMessageImportance::Important));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
