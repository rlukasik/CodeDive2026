#ifndef MATRIX_TRANSPOSED_VIEW_HPP
#define MATRIX_TRANSPOSED_VIEW_HPP

#include <cstddef>

#include "matrix_transposed.hpp"

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
class MatrixTransposedView {
    const MatrixTransposed<T, ROWS, COLUMNS>& matrix_;
public:
    using value_type = T;
    
    static constexpr std::size_t rows = COLUMNS;
    static constexpr std::size_t columns = ROWS;

    explicit MatrixTransposedView(const MatrixTransposed<T, ROWS, COLUMNS>& matrix)
        : matrix_(matrix) {}

    MatrixTransposedView(const MatrixTransposed<T, ROWS, COLUMNS>&&) = delete;

    const auto& operator()(std::size_t row, std::size_t col) const {
        return matrix_(col, row);
    }
};

#endif // MATRIX_TRANSPOSED_VIEW_HPP
