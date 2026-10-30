#ifndef MATRIX_TRANSPOSED_HPP
#define MATRIX_TRANSPOSED_HPP

#include "matrix.hpp"

template<typename T, std::size_t ROWS_ORIG, std::size_t COLUMNS_ORIG>
class MatrixTransposed: public Matrix<T, COLUMNS_ORIG, ROWS_ORIG> {
public:
    MatrixTransposed() = default;

    explicit MatrixTransposed(const Matrix<T, ROWS_ORIG, COLUMNS_ORIG>& matrix)
    {
        for (std::size_t rowIndex = 0; rowIndex < ROWS_ORIG; ++rowIndex) {
            for (std::size_t colIndex = 0; colIndex < COLUMNS_ORIG; ++colIndex) {
                (*this)(colIndex, rowIndex) = matrix(rowIndex, colIndex);
            }
        }
    }
};

#endif // MATRIX_TRANSPOSED_HPP