#ifndef MATRIX_MULTIPLIER_PRETRANSPOSED_HPP
#define MATRIX_MULTIPLIER_PRETRANSPOSED_HPP

#include "matrix.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_transposed.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Pretransposed> {
    template<typename LHS, typename RHSType, size_t RHSRows, size_t RHSColumns>
    static auto multiply(
        const LHS& lhs,
        const MatrixTransposed<RHSType, RHSRows, RHSColumns>& rhsT
    ) {
        static_assert(
            LHS::columns == RHSRows,
            "LHS columns must match the original RHS rows."
        );

        using ResultType = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), LHS::rows, RHSColumns>;
        ResultType result{};
        for (size_t i = 0; i < LHS::rows; ++i) {
            for (size_t j = 0; j < RHSColumns; ++j) {
                auto lhsRow = lhs.getRow(i);
                auto rhsTRow = rhsT.getRow(j);
                auto sum = typename ResultType::value_type{};
                for (size_t k = 0; k < LHS::columns; ++k) {
                    sum += lhsRow[k] * rhsTRow[k];
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_PRETRANSPOSED_HPP