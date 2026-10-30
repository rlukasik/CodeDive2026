#ifndef MATRIX_MULTIPLIER_SIMD_HPP
#define MATRIX_MULTIPLIER_SIMD_HPP

#include <simd>
#include <span>
#include "matrix.hpp"
#include "matrix_multiplier.hpp"
#include "matrix_transposed_view.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Simd> {
    template<typename LHS, typename RHS>
    static auto multiply(const LHS& lhs, const RHS& rhs) {
        const auto rhsTransposedView = MatrixTransposedView(rhs);
        static_assert(LHS::columns == decltype(rhsTransposedView)::rows, "Matrix dimensions do not match for multiplication.");
        using LhsSimd = std::simd::vec<typename LHS::value_type>;
        using RhsSimd = std::simd::vec<typename RHS::value_type>;
        using LhsRange = std::span<const typename LHS::value_type, LhsSimd::size()>;
        using RhsRange = std::span<const typename RHS::value_type, RhsSimd::size()>;
        using ResultType = Matrix<decltype(lhs(0, 0) * rhs(0, 0)), LHS::rows, decltype(rhsTransposedView)::columns>;
        ResultType result{};
        for (size_t i = 0; i < LHS::rows; ++i) {
            auto lhsRow = lhs.getRow(i);
            for (size_t j = 0; j < decltype(rhsTransposedView)::columns; ++j) {
                auto rhsRow = rhs.getRow(j);

                auto sum = typename ResultType::value_type{};
                size_t k = 0;
                for (; k + LhsSimd::size() <= LHS::columns; k += LhsSimd::size()) {
                    LhsRange lhsRange{lhsRow + k, LhsSimd::size()};
                    RhsRange rhsRange{rhsRow + k, RhsSimd::size()};
                    LhsSimd lhsVec{lhsRange};
                    RhsSimd rhsVec{rhsRange};
                    sum += std::simd::reduce(lhsVec * rhsVec);
                }
                for (; k < LHS::columns; ++k) {
                    sum += lhsRow[k] * rhsRow[k];
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
};

#endif // MATRIX_MULTIPLIER_SIMD_HPP
