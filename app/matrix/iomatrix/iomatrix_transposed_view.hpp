#ifndef IOMATRIX_TRANSPOSED_VIEW_HPP
#define IOMATRIX_TRANSPOSED_VIEW_HPP

#include <iostream>

#include "matrix_transposed_view.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, const MatrixTransposedView<T>& matrix_view)
{
    for (std::size_t rowIndex = 0; rowIndex < MatrixTransposedView<T>::rows; ++rowIndex) {
        std::size_t colIndex = 0;
        for (; colIndex < MatrixTransposedView<T>::columns-1; ++colIndex) {
            os << matrix_view(rowIndex, colIndex) << ",";
        }
        os << matrix_view(rowIndex, colIndex) << std::endl;
    }
    return os;
}

#endif // IOMATRIX_TRANSPOSED_VIEW_HPP
