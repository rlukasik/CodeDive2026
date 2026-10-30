#ifndef MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP
#define MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP

#include "matrix.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_transposed_view.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::WithTranspose> {
    template<typename LHS, typename RHS_TRANSPOSED>
    static auto multiply(const LHS& lhs, const RHS_TRANSPOSED& rhsT) {
        const auto rhsView = MatrixTransposedView(rhsT);
        static_assert(LHS::columns == decltype(rhsView)::rows, "Matrix dimensions do not match for multiplication.");
        using ResultType = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), LHS::rows, decltype(rhsView)::columns>;
        ResultType result{};
        for (size_t i = 0; i < LHS::rows; ++i) {
            for (size_t j = 0; j < decltype(rhsView)::columns; ++j) {
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

#endif // MATRIX_MULTIPLIER_WITH_TRANSPOSE_HPP