#include <fstream>
#include <iostream>

#include "iomatrix.hpp"
#include "matrix.hpp"
#include "matrix_cmp.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_transposed.hpp"
#include "matrix_transposed_view.hpp"

int main()
{
    using MatrixType4x16 = Matrix<int, 4, 16>;
    using MatrixType16x32 = MatrixTransposed<int, 16, 32>;

    MatrixType4x16 matrix4x16{};
    MatrixType16x32 matrix16x32{};

    std::ifstream file4x16("../input/matrix_4x16.csv");
    std::ifstream file16x32("../input/matrix_16x32.csv");

    file4x16 >> matrix4x16;
    file16x32 >> matrix16x32;

    auto resultScalar = MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(matrix4x16, MatrixTransposedView(matrix16x32));
    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix4x16, matrix16x32);

    if (!matrix_cmp(resultScalar, result)) {
        std::cerr << "Error: Results from scalar and SIMD multiplication do not match!" << std::endl;
        return 1;
    }

    std::cout << "Matrix 4x16:" << std::endl;
    std::cout << matrix4x16 << std::endl;
    std::cout << "Matrix 16x32 (transposed):" << std::endl;
    std::cout << matrix16x32 << std::endl;
    std::cout << "Matrix 16x32 (transposed view):" << std::endl;
    std::cout << MatrixTransposedView(matrix16x32) << std::endl << std::endl;
    std::cout << "Result of multiplication:" << std::endl;
    std::cout << result << std::endl;

    return 0;
}
