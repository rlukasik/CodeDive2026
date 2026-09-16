#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "matrix_policy.hpp"

template<typename T, size_t ROWS, size_t COLUMNS>
class Matrix{
    std::vector<T> data_;
public:
    using value_type = T;

    static constexpr size_t rows = ROWS;
    static constexpr size_t columns = COLUMNS;

    Matrix(): data_(ROWS * COLUMNS, T{}) {}

    T& operator()(size_t row, size_t col)
    {
        return data_[row * COLUMNS + col];
    }
    
    const T& operator()(size_t row, size_t col) const
    {
        return data_[row * COLUMNS + col];
    }

    auto transpose() const {
        Matrix<T, COLUMNS, ROWS> transposed;
        for (size_t rowIndex = 0; rowIndex < ROWS; ++rowIndex) {
            for (size_t colIndex = 0; colIndex < COLUMNS; ++colIndex) {
                transposed(colIndex, rowIndex) = (*this)(rowIndex, colIndex);
            }
        }
        return transposed;
    }

    const T* getRow(size_t row) const {
        return &data_[row * COLUMNS];
    }
};

template<typename T, size_t ROWS, size_t COLUMNS>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLUMNS>& matrix)
{
    for (size_t rowIndex = 0; rowIndex < ROWS; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < COLUMNS; ++colIndex) {
            os << matrix(rowIndex, colIndex) << " ";
        }
        os << std::endl;
    }
    return os;
}

template<typename T, size_t ROWS, size_t COLUMNS>
std::istream& operator>>(std::istream& is, Matrix<T, ROWS, COLUMNS>& matrix)
{
    std::string row;
    for (size_t rowIndex = 0; rowIndex < ROWS && std::getline(is, row); ++rowIndex) {
        std::istringstream rowStream(row);
        std::string value;
        size_t colIndex = 0;
        for (size_t columnIndex = 0; columnIndex < COLUMNS && std::getline(rowStream, value, ','); ++colIndex) {
            matrix(rowIndex, colIndex) = static_cast<T>(std::stod(value) + 0.5);
        }
    }
    return is;
}

#endif // MATRIX_HPP
