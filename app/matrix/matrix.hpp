#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<typename T, size_t ROWS, size_t COLUMNS>
class Matrix{
    std::vector<T> data_;
public:
    using value_type = T;

    static constexpr size_t rows = ROWS;
    static constexpr size_t columns = COLUMNS;

    Matrix(): data_(ROWS * COLUMNS, T{}) {}

    T& operator()(size_t row, size_t col)
    {
        return data_[row * COLUMNS + col];
    }
    
    const T& operator()(size_t row, size_t col) const
    {
        return data_[row * COLUMNS + col];
    }

    const T* getRow(size_t row) const {
        return &data_[row * COLUMNS];
    }
};

#endif // MATRIX_HPP
