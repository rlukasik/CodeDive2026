#ifndef IOMATRIX_BASIC_HPP
#define IOMATRIX_BASIC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <type_traits>

#include "matrix.hpp"

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLUMNS>& matrix)
{
    for (std::size_t rowIndex = 0; rowIndex < ROWS; ++rowIndex) {
        for (std::size_t colIndex = 0; colIndex < COLUMNS; ++colIndex) {
            os << matrix(rowIndex, colIndex) << " ";
        }
        os << std::endl;
    }
    return os;
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

#endif // IOMATRIX_BASIC_HPP