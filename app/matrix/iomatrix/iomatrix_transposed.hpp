#ifndef IOMATRIX_TRANSPOSED_HPP
#define IOMATRIX_TRANSPOSED_HPP

#include "matrix_transposed.hpp"

template<typename T, size_t ROWS, size_t COLUMNS>
std::istream& operator>>(std::istream& is, MatrixTransposed<T, ROWS, COLUMNS>& matrixTransposed)
{
    std::string row;
    for (size_t rowIndex = 0; rowIndex < ROWS && std::getline(is, row); ++rowIndex) {
        std::istringstream rowStream(row);
        std::string value;
        for (size_t colIndex = 0; colIndex < COLUMNS && std::getline(rowStream, value, ','); ++colIndex) {
            matrixTransposed(colIndex, rowIndex) = static_cast<T>(std::stod(value) + 0.5);
        }
    }
    return is;
}

#endif // IOMATRIX_TRANSPOSED_HPP
