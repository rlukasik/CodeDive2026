#ifndef IOMATRIX_TRANSPOSED_HPP
#define IOMATRIX_TRANSPOSED_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <type_traits>

#include "matrix_transposed.hpp"

template<typename T, std::size_t ROWS_ORIG, std::size_t COLUMNS_ORIG>
std::istream& operator>>(std::istream& is, MatrixTransposed<T, ROWS_ORIG, COLUMNS_ORIG>& matrixTransposed)
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

#endif // IOMATRIX_TRANSPOSED_HPP
