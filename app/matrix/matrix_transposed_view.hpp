#ifndef MATRIX_TRANSPOSED_VIEW_HPP
#define MATRIX_TRANSPOSED_VIEW_HPP

template<typename T>
class MatrixTransposedView {
    const T& matrix_;
public:
    using value_type = typename T::value_type;
    
    static constexpr size_t rows = T::columns;
    static constexpr size_t columns = T::rows;

    explicit MatrixTransposedView(const T& matrix)
        : matrix_(matrix) {}

    const auto& operator()(size_t row, size_t col) const {
        return matrix_(col, row);
    }

};

#endif // MATRIX_TRANSPOSED_VIEW_HPP
