#ifndef MATRIX_MULTIPLIER_SIMD_HPP
#define MATRIX_MULTIPLIER_SIMD_HPP

#include <simd>
#include <span>
#include "matrix.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_transposed_view.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Simd> {
    template<typename LHS, typename RHS_TRANSPOSED>
    static auto multiply(const LHS& lhs, const RHS_TRANSPOSED& rhsT) {
        const auto rhsView = MatrixTransposedView(rhsT);
        static_assert(LHS::columns == decltype(rhsView)::rows, "Matrix dimensions do not match for multiplication.");
        using LhsSimd = std::simd::vec<typename LHS::value_type>;
        using RhsTSimd = std::simd::vec<typename RHS_TRANSPOSED::value_type>;
        using LhsRange = std::span<const typename LHS::value_type, LhsSimd::size()>;
        using RhsTRange = std::span<const typename RHS_TRANSPOSED::value_type, RhsTSimd::size()>;
        using ResultType = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), LHS::rows, decltype(rhsView)::columns>;
        ResultType result{};
        for (size_t i = 0; i < LHS::rows; ++i) {
            auto lhsRow = lhs.getRow(i);
            for (size_t j = 0; j < decltype(rhsView)::columns; ++j) {
                auto rhsTRow = rhsT.getRow(j);

                auto sum = typename ResultType::value_type{};
                size_t k = 0;
                for (; k + LhsSimd::size() <= LHS::columns; k += LhsSimd::size()) {
                    LhsRange lhsRange{lhsRow + k, LhsSimd::size()};
                    RhsTRange rhsTRange{rhsTRow + k, RhsTSimd::size()};
                    LhsSimd lhsVec{lhsRange};
                    RhsTSimd rhsTVec{rhsTRange};
                    sum += std::simd::reduce(lhsVec * rhsTVec);
                }
                for (; k < LHS::columns; ++k) {
                    sum += lhsRow[k] * rhsTRow[k];
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_SIMD_HPP
