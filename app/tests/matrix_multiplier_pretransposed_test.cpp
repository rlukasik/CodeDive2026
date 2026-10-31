#include <gtest/gtest.h>

#include "matrix_multiplier_pretransposed.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier_test.hpp"

TEST_F(MatrixMultiplierTest, PretransposedMultiplies4x16By16x32Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(matrix4x16, matrix16x32);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}

TEST_F(MatrixMultiplierTest, PretransposedMultiplies1024x2048By2048x3072Correctly) {
    auto result = MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(matrix1024x2048, matrix2048x3072);

    EXPECT_TRUE(matrix_cmp(result, expectedLargeResult));
}
