#include "Core/core.h"
#include "Core/graphics.h"
#include "gtest.h"


#if !defined(SFML)
    #error Only SFML supported now.
#endif //SFML

using namespace Graphics;


TEST(graphicsTest, argb_test_1) {
    constexpr ARGB argb(0x55667788u);

    EXPECT_EQ(0x55667788u, static_cast<uint>(argb));
    EXPECT_EQ(0x55u, argb.a);
    EXPECT_EQ(0x66u, argb.r);
    EXPECT_EQ(0x77u, argb.g);
    EXPECT_EQ(0x88u, argb.b);
}

TEST(graphicsTest, argb_test_2) {
    constexpr ARGB argb(0x66u, 0x77u, 0x88u, 0x55u);

    EXPECT_EQ(0x55667788u, static_cast<uint>(argb));
    EXPECT_EQ(0x55u, argb.a);
    EXPECT_EQ(0x66u, argb.r);
    EXPECT_EQ(0x77u, argb.g);
    EXPECT_EQ(0x88u, argb.b);
}

TEST(graphicsTest, argb_test_3) {
    const TColor color(0x66u, 0x77u, 0x88u, 0x55u);
    ARGB argb(color);

    EXPECT_EQ(0x55667788u, static_cast<uint>(argb));
    EXPECT_EQ(0x55u, argb.a);
    EXPECT_EQ(0x66u, argb.r);
    EXPECT_EQ(0x77u, argb.g);
    EXPECT_EQ(0x88u, argb.b);
}





int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
