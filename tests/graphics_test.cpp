#include "GameEngine/Utility/core.h"
#include "GameEngine/Utility/graphics.h"
#include "gtest/gtest.h"



using namespace Graphics;


TEST(argbTest, argb_from_uint32) {
    constexpr uint color = 0x55667788u;
    constexpr uint colorA = 0x55u;
    constexpr uint colorR = 0x66u;
    constexpr uint colorG = 0x77u;
    constexpr uint colorB = 0x88u;

    constexpr ARGB argb(color);

    ASSERT_EQ(color, static_cast<uint>(argb));
    EXPECT_EQ(colorA, argb.a);
    EXPECT_EQ(colorR, argb.r);
    EXPECT_EQ(colorG, argb.g);
    EXPECT_EQ(colorB, argb.b);
}

TEST(argbTest, argb_from_RGBA_8_8_8_8) {
    constexpr uint color = 0x55667788u;
    constexpr uint colorA = 0x55u;
    constexpr uint colorR = 0x66u;
    constexpr uint colorG = 0x77u;
    constexpr uint colorB = 0x88u;

    constexpr ARGB argb(colorR, colorG, colorB, colorA);

    ASSERT_EQ(color, static_cast<uint>(argb));
    EXPECT_EQ(colorA, argb.a);
    EXPECT_EQ(colorR, argb.r);
    EXPECT_EQ(colorG, argb.g);
    EXPECT_EQ(colorB, argb.b);
}

TEST(argbTest, argb_from_sf_color) {
    constexpr uint color = 0x55667788u;
    constexpr uint colorA = 0x55u;
    constexpr uint colorR = 0x66u;
    constexpr uint colorG = 0x77u;
    constexpr uint colorB = 0x88u;

    const ARGB argb(TColor(colorR, colorG, colorB, colorA));

    ASSERT_EQ(color, static_cast<uint>(argb));
    EXPECT_EQ(colorA, argb.a);
    EXPECT_EQ(colorR, argb.r);
    EXPECT_EQ(colorG, argb.g);
    EXPECT_EQ(colorB, argb.b);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
