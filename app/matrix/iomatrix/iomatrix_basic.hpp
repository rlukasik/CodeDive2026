#ifndef IOMATRIX_BASIC_HPP
#define IOMATRIX_BASIC_HPP

#include "matrix.hpp"

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
        for (size_t colIndex = 0; colIndex < COLUMNS && std::getline(rowStream, value, ','); ++colIndex) {
            matrix(rowIndex, colIndex) = static_cast<T>(std::stod(value) + 0.5);
        }
    }
    return is;
}

#endif // IOMATRIX_BASIC_HPP