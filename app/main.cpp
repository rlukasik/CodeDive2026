#include <fstream>
#include <memory>

#include "matrix.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_policy.hpp"

int main()
{
    using MatrixType4x16 = Matrix<int, 4, 16>;
    using MatrixType16x32 = Matrix<int, 16, 32>;

    MatrixType4x16 matrix4x16{};
    MatrixType16x32 matrix16x32{};

    std::ifstream file4x16("../input/matrix_4x16.csv");
    std::ifstream file16x32("../input/matrix_16x32.csv");

    file4x16 >> matrix4x16;
    file16x32 >> matrix16x32;

    auto result = MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(matrix4x16, matrix16x32);

    std::cout << "Result of multiplication:" << std::endl;
    std::cout << result << std::endl;

    return 0;
}
