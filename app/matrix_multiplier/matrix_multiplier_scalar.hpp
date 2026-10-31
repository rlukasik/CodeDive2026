#ifndef MATRIX_MULTIPLIER_SCALAR_HPP
#define MATRIX_MULTIPLIER_SCALAR_HPP

#include "matrix.hpp"
#include "matrix_multiplier_fwd.hpp"
#include "matrix_transposed.hpp"
#include "matrix_transposed_view.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Scalar> {
    template<typename LHS, typename RHSType, std::size_t RHSRows, std::size_t RHSColumns>
    static auto multiply(
        const LHS& lhs, 
        const MatrixTransposed<RHSType, RHSRows, RHSColumns>& rhsT
    ) {
        static_assert(
            LHS::columns == RHSRows,
            "LHS columns must match RHS rows."
        );

        auto rhs = MatrixTransposedView(rhsT);
        using ResultType = Matrix<decltype(lhs(0, 0) * rhs(0, 0)), LHS::rows, RHSColumns>;
        ResultType result{};
        for (std::size_t i = 0; i < LHS::rows; ++i) {
            for (std::size_t j = 0; j < RHSColumns; ++j) {
                for (std::size_t k = 0; k < LHS::columns; ++k) {
                    result(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_SCALAR_HPP
