#include "gtest.h"
#include "poly.h" 



TEST(PolyTest, can_create_empty_poly) {
    ASSERT_NO_THROW(poly p());
}
TEST(PolyTest, equal) {
    poly p1("5x2+3+y+8");
    poly p2 = p1;
    EXPECT_TRUE(p1 == p2);
}
TEST(PolyTest, not_equal) {
    poly p1("5x2+3+y+8");
    poly p2("x-z");
    EXPECT_TRUE(p1 != p2);
}

TEST(PolyTest, ParsePoly) {
    poly p("3x2y4z+5x3-2.5y2+4z2");
    poly expected ("5x3+3x2y4z-2.5y2+4z2");
    EXPECT_EQ(p,expected);
}

TEST(PolyTest, addition) {
    poly p1("3xy2z+2y");
    poly p2 ("5x2+3+y+8");
    poly result = p1 + p2;
    poly expected("5x2+3xy2z+3y+11");
    EXPECT_EQ(result, expected);
}

TEST(PolyTest, multiplication) {
    poly p1("x+1");
    poly p2("x-z");
    poly result = p1 * p2;
    poly expected("x2-xz+x-z");
    EXPECT_EQ(result, expected);
}
TEST(PolyTest, mult_scalar) {
    poly p("3x2y4z+5x3-2.5y2+4z2");
    poly p2 = p * 2;
    poly expected("6x2y4z+10x3-5y2+8z2");
    EXPECT_EQ(expected, p2);
}
TEST(PolyTest,zero_result_subtraction) {
    poly p1("2x2y4z4+6x2y");
    poly p2 = p1;
    poly p3 = p1 - p2;
    EXPECT_EQ(poly(), p3);
}
TEST(PolyTest,subtaction) {
    poly p1("2x2y4z4+6x2y");
    poly p2("x-z");
    poly p3 = p1 - p2;
    poly expected("2x2y4z4+6x2y-x+z");
    EXPECT_EQ(expected, p3);
}
TEST(PolyTest, at_point) {
    poly p("2x+3y+z");
    double result = p.at_point(1, 1, 1);
    EXPECT_DOUBLE_EQ(result, 6);
}

