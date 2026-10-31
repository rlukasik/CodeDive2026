#include <gtest/gtest.h>

#include "matrix_multiplier_scalar.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier_test.hpp"

TEST_F(MatrixMultiplierTest, ScalarMultiplies4x16By16x32Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix4x16, matrix16x32);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}

TEST_F(MatrixMultiplierTest, ScalarMultiplies1024x2048By2048x3072Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix1024x2048, matrix2048x3072);

    EXPECT_TRUE(matrix_cmp(result, expectedLargeResult));
}
