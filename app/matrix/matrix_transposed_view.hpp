#ifndef MATRIX_TRANSPOSED_VIEW_HPP
#define MATRIX_TRANSPOSED_VIEW_HPP

#include <cstddef>

template<typename T>
class MatrixTransposedView {
    const T& matrix_;
public:
    using value_type = typename T::value_type;
    
    static constexpr std::size_t rows = T::columns;
    static constexpr std::size_t columns = T::rows;

    explicit MatrixTransposedView(const T& matrix)
        : matrix_(matrix) {}

    MatrixTransposedView(const T&&) = delete;

    const auto& operator()(std::size_t row, std::size_t col) const {
        return matrix_(col, row);
    }
};

#endif // MATRIX_TRANSPOSED_VIEW_HPP
