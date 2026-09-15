#ifndef MATRIX_MULTIPLIER_SCALAR_HPP
#define MATRIX_MULTIPLIER_SCALAR_HPP

#include "matrix_multiplier.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Scalar> {
    template<typename LHS, typename RHS>
    static auto multiply(const LHS& lhs, const RHS& rhs) {
        using ResultType = Matrix<decltype(lhs(0, 0) * rhs(0, 0)), LHS::rows, RHS::columns, MultiplicationPolicy::Scalar>;
        ResultType result{};
        for (size_t i = 0; i < LHS::rows; ++i) {
            for (size_t j = 0; j < RHS::columns; ++j) {
                for (size_t k = 0; k < LHS::columns; ++k) {
                    result(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_SCALAR_HPP
