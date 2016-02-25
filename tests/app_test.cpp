#include "Application/application.h"
#include "gtest.h"


class TestApplication :
    public ::testing::Test,
    public TApplication
{
protected:
    static TApplicationInfo info() {
        TApplicationInfo info_;
        info.appTitle = L"TEST";
        info.style = sf::Style::Default;
        info.windowWidth = 400;
        info.windowHeight = 400;
        return info_;
    }

    TestApplication() :
        TApplication(info())
    {}
}


TEST_F(TestApplication, initialization) {
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
