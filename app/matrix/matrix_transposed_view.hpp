#ifndef MATRIX_TRANSPOSED_VIEW_HPP
#define MATRIX_TRANSPOSED_VIEW_HPP

#include <iostream>

template<typename T>
class MatrixTransposedView {
    const T& matrix_;
public:
    using value_type = typename T::value_type;
    
    static constexpr size_t rows = T::columns;
    static constexpr size_t columns = T::rows;

    explicit MatrixTransposedView(const T& matrix)
        : matrix_(matrix) {}

    MatrixTransposedView(const T&&) = delete;

    const auto& operator()(size_t row, size_t col) const {
        return matrix_(col, row);
    }
};

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

#endif // MATRIX_TRANSPOSED_VIEW_HPP
