#include <gtest/gtest.h>

#include "matrix_multiplier_simd.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier_test.hpp"

TEST_F(MatrixMultiplierTest, SimdMultiplies4x16By16x32Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix4x16, matrix16x32);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}

TEST_F(MatrixMultiplierTest, SimdMultiplies1024x2048By2048x3072Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix1024x2048, matrix2048x3072);

    EXPECT_TRUE(matrix_cmp(result, expectedLargeResult));
}
