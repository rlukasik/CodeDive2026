#ifndef MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP
#define MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP

#include "matrix_multiplier.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::WithTranspose> {
    template<typename LHS, typename RHS>
    static auto multiply(const LHS& lhs, const RHS& rhs) {
        using ResultType = Matrix<decltype(lhs(0, 0) * rhs(0, 0)), LHS::rows, RHS::columns, MultiplicationPolicy::WithTranspose>;
        ResultType result{};
        const auto rhsT = rhs.transpose();
        for (size_t i = 0; i < LHS::rows; ++i) {
            for (size_t j = 0; j < RHS::columns; ++j) {
                auto lhsRow = lhs.getRow(i);
                auto rhsRow = rhsT.getRow(j);
                auto sum = typename ResultType::value_type{};
                for (size_t k = 0; k < LHS::columns; ++k) {
                    sum += lhsRow[k] * rhsRow[k];
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP