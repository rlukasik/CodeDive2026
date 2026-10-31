#include <gtest/gtest.h>

#include "matrix_multiplier_simd.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier_test.hpp"

TEST_F(MatrixMultiplierTest, Multiply) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix4x16, matrix16x32);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}
