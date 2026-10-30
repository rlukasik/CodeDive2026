#ifndef IOMATRIX_TRANSPOSED_VIEW_HPP
#define IOMATRIX_TRANSPOSED_VIEW_HPP

#include "matrix_transposed_view.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, const MatrixTransposedView<T>& matrix_view)
{
    for (size_t rowIndex = 0; rowIndex < MatrixTransposedView<T>::rows; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < MatrixTransposedView<T>::columns; ++colIndex) {
            os << matrix_view(rowIndex, colIndex) << " ";
        }
        os << std::endl;
    }
    return os;
}

#endif // IOMATRIX_TRANSPOSED_VIEW_HPP
