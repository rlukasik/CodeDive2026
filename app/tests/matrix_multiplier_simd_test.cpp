#include <gtest/gtest.h>
#include <fstream>

#include "iomatrix.hpp"
#include "matrix_multiplier_simd.hpp"
#include "matrix_cmp.hpp"

TEST(MatrixMultiplierSIMD, Multiply) {
    using MatrixType4x16 = Matrix<int, 4, 16>;
    using MatrixType16x32 = MatrixTransposed<int, 16, 32>;
    using ExpectedType = Matrix<int, 4, 32>;

    MatrixType4x16 matrix4x16{};
    MatrixType16x32 matrix16x32{};
    ExpectedType expectedResult{};

    std::ifstream file4x16("../input/matrix_4x16.csv");
    std::ifstream file16x32("../input/matrix_16x32.csv");
    std::ifstream fileExpected("../expected/matrix_4x32.csv");

    file4x16 >> matrix4x16;
    file16x32 >> matrix16x32;
    fileExpected >> expectedResult;

    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix4x16, matrix16x32);

    EXPECT_TRUE(matrix_cmp(result, expectedResult));
}
