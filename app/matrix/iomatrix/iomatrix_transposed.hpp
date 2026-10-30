#ifndef IOMATRIX_TRANSPOSED_HPP
#define IOMATRIX_TRANSPOSED_HPP

#include <iostream>
#include <string>
#include <sstream>

#include "matrix_transposed.hpp"

template<typename T, size_t ROWS_ORIG, size_t COLUMNS_ORIG>
std::istream& operator>>(std::istream& is, MatrixTransposed<T, ROWS_ORIG, COLUMNS_ORIG>& matrixTransposed)
{
    std::string row;
    for (size_t rowIndex = 0; rowIndex < ROWS_ORIG && std::getline(is, row); ++rowIndex) {
        std::istringstream rowStream(row);
        std::string value;
        for (size_t colIndex = 0; colIndex < COLUMNS_ORIG && std::getline(rowStream, value, ','); ++colIndex) {
            matrixTransposed(colIndex, rowIndex) = static_cast<T>(std::stod(value) + 0.5);
        }
    }
    return is;
}

#endif // IOMATRIX_TRANSPOSED_HPP
