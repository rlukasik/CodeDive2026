#ifndef IOMATRIX_HPP
#define IOMATRIX_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <type_traits>

#include "matrix.hpp"
#include "matrix_transposed.hpp"
#include "matrix_transposed_view.hpp"

template<typename T>
std::ostream& omatrix_stream(std::ostream& os, const T& matrix)
{
    for (std::size_t rowIndex = 0; rowIndex < T::rows; ++rowIndex) {
        std::size_t colIndex = 0;
        for (; colIndex < T::columns-1; ++colIndex) {
            os << matrix(rowIndex, colIndex) << ",";
        }
        os << matrix(rowIndex, colIndex) << std::endl;
    }
    return os;
}

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLUMNS>& matrix)
{
    return omatrix_stream(os, matrix);
}

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
std::istream& operator>>(std::istream& is, Matrix<T, ROWS, COLUMNS>& matrix)
{
    std::string row;
    for (std::size_t rowIndex = 0; rowIndex < ROWS && std::getline(is, row); ++rowIndex) {
        std::istringstream rowStream(row);
        std::string value;
        for (std::size_t colIndex = 0; colIndex < COLUMNS && std::getline(rowStream, value, ','); ++colIndex) {
            const double parsed = std::stod(value);
            if constexpr (std::is_integral_v<T>) {
                matrix(rowIndex, colIndex) = static_cast<T>(std::round(parsed));
            } else {
                matrix(rowIndex, colIndex) = static_cast<T>(parsed);
            }
        }
    }
    return is;
}

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
std::ostream& operator<<(std::ostream& os, const MatrixTransposed<T, ROWS, COLUMNS>& matrix)
{
    return omatrix_stream(os, matrix);
}

template<typename T, std::size_t ROWS_ORIG, std::size_t COLUMNS_ORIG>
std::istream& operator>>(std::istream& is, MatrixTransposed<T, COLUMNS_ORIG, ROWS_ORIG>& matrixTransposed)
{
    std::string row;
    for (std::size_t rowIndex = 0; rowIndex < ROWS_ORIG && std::getline(is, row); ++rowIndex) {
        std::istringstream rowStream(row);
        std::string value;
        for (std::size_t colIndex = 0; colIndex < COLUMNS_ORIG && std::getline(rowStream, value, ','); ++colIndex) {
            const double parsed = std::stod(value);
            if constexpr (std::is_integral_v<T>) {
                matrixTransposed(colIndex, rowIndex) = static_cast<T>(std::round(parsed));
            } else {
                matrixTransposed(colIndex, rowIndex) = static_cast<T>(parsed);
            }
        }
    }
    return is;
}

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
std::ostream& operator<<(std::ostream& os, const MatrixTransposedView<T, ROWS, COLUMNS>& matrix)
{
    return omatrix_stream(os, matrix);
}

#endif // IOMATRIX_HPP
