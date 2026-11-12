#include <gtest/gtest.h>

#include "matrix_multiplier_scalar.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier_test.hpp"

TEST_F(MatrixMultiplierTest, ScalarMultiplies4x16By16x32Correctly) {
    auto result = Matrix<decltype(matrix4x16(0, 0) * matrix16x32(0, 0)), MatrixType4x16::rows, MatrixType16x32::rows>{};
    MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix4x16, matrix16x32, result);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}

TEST_F(MatrixMultiplierTest, ScalarMultiplies1024x2048By2048x3072Correctly) {
    auto result = Matrix<decltype(matrix1024x2048(0, 0) * matrix2048x3072(0, 0)), MatrixType1024x2048::rows, MatrixType2048x3072::rows>{};
    MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix1024x2048, matrix2048x3072, result);

    EXPECT_TRUE(matrix_cmp(result, expectedLargeResult));
}

TEST_F(MatrixMultiplierTest, ScalarMultiplies1024x2048By2048x3072DoubleCorrectly) {
    auto result = Matrix<decltype(matrix1024x2048Double(0, 0) * matrix2048x3072Double(0, 0)), MatrixType1024x2048Double::rows, MatrixType2048x3072Double::rows>{};
    MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix1024x2048Double, matrix2048x3072Double, result);

    EXPECT_TRUE(matrix_cmp(result, expectedLargeResultDouble));
}
