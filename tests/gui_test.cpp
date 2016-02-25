#include "Application/application.h"
#include "GUI/gui_main.h"
#include "GUI/uiparent.h"
#include "gtest.h"


using namespace GUI;

TEST(UIParent_test, initialization) {
    TApplicationInfo info;
    info.appTitle = TEXT("Test");
    info.style = sf::Style::Default;
    info.windowWidth = 400;
    info.windowHeight = 400;
    TApplication& app = TApplication::Create(info);
    
    TUIParentSource source;
    source.size = TSize(300, 200);
    source.margin = TPadding(1, 2, 3, 4);
    source.show = true;
    source.position = TCoordinate(100, 200);
    TUIParent uiparent(source);

    EXPECT_EQ(TSize(300, 200), uiparent.GetOwnSize());
    EXPECT_EQ(TSize(300 + 3 + 4, 200 + 1 + 2), uiparent.GetSize());
    EXPECT_EQ(true, uiparent.IsShown());
    EXPECT_EQ(TPadding(1, 2, 3, 4), uiparent.GetMargin());
    EXPECT_EQ(TCoordinate(100, 200), uiparent.GetPosition());

    string name = TGUISettings::DEFAULT_UIPARENT_NAME;
    EXPECT_EQ(name, uiparent.GetName());

    EXPECT_NO_THROW(uiparent.SetMargin(TPadding(3, 4, 5, 6)));
    EXPECT_NO_THROW(uiparent.SetPosition(TCoordinate(300, 400)));
    EXPECT_NO_THROW(uiparent.SetSize(TSize(100, 200)));
    EXPECT_THROW(uiparent.SetParent(uiparent.shared_from_this()), exception);
    EXPECT_NO_THROW(uiparent.SetVisibility(false));

    EXPECT_EQ(TSize(100 + 5 + 6, 200 + 3 + 4), uiparent.GetSize());
    EXPECT_EQ(TPadding(3, 4, 5, 6), uiparent.GetMargin());
    EXPECT_EQ(TCoordinate(300, 400), uiparent.GetPosition());
    EXPECT_FALSE(uiparent.IsShown());
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
