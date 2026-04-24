#include <gtest/gtest.h>
#include "math_utils.h"

// Test suite for math_utils::add
TEST(MathUtilsTest, AddPositiveNumbers) {
    EXPECT_EQ(math_utils::add(2, 3), 5);
}

TEST(MathUtilsTest, AddNegativeNumbers) {
    EXPECT_EQ(math_utils::add(-2, -3), -5);
}

TEST(MathUtilsTest, AddMixedSignNumbers) {
    EXPECT_EQ(math_utils::add(-5, 3), -2);
}

TEST(MathUtilsTest, AddZero) {
    EXPECT_EQ(math_utils::add(0, 0), 0);
    EXPECT_EQ(math_utils::add(5, 0), 5);
    EXPECT_EQ(math_utils::add(0, -5), -5);
}