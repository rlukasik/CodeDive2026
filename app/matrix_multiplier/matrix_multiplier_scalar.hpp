#ifndef MATRIX_MULTIPLIER_SCALAR_HPP
#define MATRIX_MULTIPLIER_SCALAR_HPP

#include "matrix.hpp"
#include "matrix_multiplier_fwd.hpp"
#include "matrix_transposed.hpp"
#include "matrix_transposed_view.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Scalar> {
    template<typename LHS, typename RHSTType, std::size_t RHSTRows, std::size_t RHSTColumns>
    static auto& multiply(
        const LHS& lhs, 
        const MatrixTransposed<RHSTType, RHSTRows, RHSTColumns>& rhsT,
        Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), LHS::rows, RHSTRows>& result
    ) {
        static_assert(
            LHS::columns == RHSTColumns,
            "LHS columns must match RHST (T - Transposed) columns."
        );

        auto rhs = MatrixTransposedView(rhsT);
        using Result = std::remove_cvref_t<decltype(result)>;
        for (std::size_t i = 0; i < LHS::rows; ++i) {
            for (std::size_t j = 0; j < RHSTRows; ++j) {
                auto sum = typename Result::value_type{};
                for (std::size_t k = 0; k < LHS::columns; ++k) {
                    sum += lhs(i, k) * rhs(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_SCALAR_HPP
