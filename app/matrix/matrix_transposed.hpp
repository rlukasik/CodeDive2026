#ifndef MATRIX_TRANSPOSED_HPP
#define MATRIX_TRANSPOSED_HPP

#include <cstddef>
#include <vector>

#include "matrix.hpp"

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
class MatrixTransposed {
    std::vector<T> data_;
public:
    using value_type = T;

    static constexpr std::size_t rows = ROWS;
    static constexpr std::size_t columns = COLUMNS;
    
    MatrixTransposed(): data_(ROWS * COLUMNS, T{}) {}

    explicit MatrixTransposed(const Matrix<T, COLUMNS, ROWS>& matrix)
    {
        for (std::size_t rowIndex = 0; rowIndex < COLUMNS; ++rowIndex) {
            for (std::size_t colIndex = 0; colIndex < ROWS; ++colIndex) {
                (*this)(colIndex, rowIndex) = matrix(rowIndex, colIndex);
            }
        }
    }

    T& operator()(std::size_t row, std::size_t col)
    {
        return data_[row * COLUMNS + col];
    }
    
    const T& operator()(std::size_t row, std::size_t col) const
    {
        return data_[row * COLUMNS + col];
    }

    const T* getRow(std::size_t row) const {
        return &data_[row * COLUMNS];
    }
};

#endif // MATRIX_TRANSPOSED_HPP
