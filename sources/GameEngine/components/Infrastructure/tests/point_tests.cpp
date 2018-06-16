#include "gtest/gtest.h"

#include "GameEngine/Utility/data_structures.h"


using namespace GE;

class PointTest :
    public ::testing::Test
{
protected:
    using Point = Point2i;
    static const Point p1;
    static const Point p2;
};
const PointTest::Point PointTest::p1 {10, 15};
const PointTest::Point PointTest::p2 {4, 5};

TEST_F(PointTest, operator_lesser) {
    ASSERT_FALSE(p1 < p2);
}

TEST_F(PointTest, operator_greater) {
    ASSERT_TRUE(p1 > p2);
}

TEST_F(PointTest, operator_equals) {
    ASSERT_FALSE(p1 == p2);
}

TEST_F(PointTest, operator_not_equals) {
    ASSERT_TRUE(p1 != p2);
}

TEST_F(PointTest, operator_subtraction) {
    ASSERT_EQ(Point(6, 10), p1 - p2);
}

TEST_F(PointTest, operator_sum) {
    ASSERT_EQ(Point(14, 20), p1 + p2);
}

TEST_F(PointTest, operator_multiplication) {
    ASSERT_EQ(Point(20, 45), p1 * Point(2, 3));
}

TEST_F(PointTest, operator_division) {
    ASSERT_EQ(Point(2, 3), p1 / Point(5, 5));
}

TEST_F(PointTest, operator_multiplication_by_number) {
    ASSERT_EQ(Point(50, 75), p1 * 5);
}

TEST_F(PointTest, operator_division_by_number) {
    ASSERT_EQ(Point(2, 3), p1 / 5);
}

TEST_F(PointTest, operator_add_number) {
    ASSERT_EQ(Point(12, 17), p1 + 2);
}

TEST_F(PointTest, operator_subtract_number) {
    ASSERT_EQ(Point(8, 13), p1 - 2);
}

TEST_F(PointTest, operator_iadd) {
    auto p3 = p1;
    p3 += p2;
    ASSERT_EQ(Point(14, 20), p3);
}

TEST_F(PointTest, operator_at) {
#if defined(_DEBUG)
    EXPECT_ANY_THROW(p1[3]);
#else
    EXPECT_NO_THROW(p1[3]);
#endif
}

TEST_F(PointTest, operation_norm) {
    ASSERT_DOUBLE_EQ(5.0, norm(Point(3, 4)));
}

TEST_F(PointTest, operation_norm_squared) {
    ASSERT_DOUBLE_EQ(25.0, norm(Point(3, 4), NormType::NORM_SQUARED));
}

TEST_F(PointTest, operation_module) {
    ASSERT_EQ(Point(1, 2), abs(Point(-1, 2)));
}

TEST_F(PointTest, operation_in_rect_positive_simple) {
    ASSERT_TRUE(Point(1, 2).isInRect(
        Point(0, 1), Point(2, 3)
    ));
}

TEST_F(PointTest, operation_in_rect_positive_inversed_bounds) {
    ASSERT_TRUE(Point(1, 2).isInRect(
        Point(2, 3), Point(0, 1)
    ));
}

TEST_F(PointTest, operation_in_rect_negative_simple) {
    ASSERT_FALSE(Point(1, 2).isInRect(
        Point(1, 3), Point(2, 3)
    ));
}

TEST_F(PointTest, operation_in_rect_negative_inversed_bounds) {
    ASSERT_FALSE(Point(1, 2).isInRect(
        Point(2, 3), Point(1, 3)
    ));
}

TEST(pointTest, serialization) {
    using Point = Point<double, 5>;
    Point point {4.0, 2.0, 1.0, 1.0, 6.0};

    EXPECT_FALSE(string(point).empty());

#if defined(UNICODE)
    EXPECT_FALSE(wstring(point).empty());
#endif
}