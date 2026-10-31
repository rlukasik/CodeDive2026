#ifndef MATRIX_MULTIPLIER_TEST_HPP
#define MATRIX_MULTIPLIER_TEST_HPP

#include <gtest/gtest.h>
#include <fstream>

#include "iomatrix.hpp"
#include "matrix.hpp"
#include "matrix_transposed.hpp"

class MatrixMultiplierTest : public ::testing::Test {
protected:
    using MatrixType4x16 = Matrix<int, 4, 16>;
    using MatrixType16x32 = MatrixTransposed<int, 16, 32>;
    using ExpectedType = Matrix<int, 4, 32>;

    inline static MatrixType4x16 matrix4x16{};
    inline static MatrixType16x32 matrix16x32{};
    inline static ExpectedType expectedResult{};

    static void SetUpTestSuite() {
        // Code here will be called once before all tests in this test suite.
        std::ifstream file4x16("../input/matrix_4x16.csv");
        std::ifstream file16x32("../input/matrix_16x32.csv");
        std::ifstream fileExpected("../expected/matrix_4x32.csv");

        ASSERT_TRUE(file4x16.is_open()) << "Cannot open matrix_4x16.csv";
        ASSERT_TRUE(file16x32.is_open()) << "Cannot open matrix_16x32.csv";
        ASSERT_TRUE(fileExpected.is_open()) << "Cannot open matrix_4x32.csv";

        ASSERT_TRUE(static_cast<bool>(file4x16 >> matrix4x16));
        ASSERT_TRUE(static_cast<bool>(file16x32 >> matrix16x32));
        ASSERT_TRUE(static_cast<bool>(fileExpected >> expectedResult));
    }
};

#endif // MATRIX_MULTIPLIER_TEST_HPP