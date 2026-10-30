#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <vector>

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
class Matrix{
    std::vector<T> data_;
public:
    using value_type = T;

    static constexpr std::size_t rows = ROWS;
    static constexpr std::size_t columns = COLUMNS;

    Matrix(): data_(ROWS * COLUMNS, T{}) {}

    T& operator()(std::size_t row, std::size_t col)
    {
        return data_[row * COLUMNS + col];
    }
    
    const T& operator()(std::size_t row, std::size_t col) const
    {
        return data_[row * COLUMNS + col];
    }

    const T* getRow(std::size_t row) const {
        return &data_[row * COLUMNS];
    }
};

#endif // MATRIX_HPP
