#ifndef MATRIX_MULTIPLIER_SIMD_HPP
#define MATRIX_MULTIPLIER_SIMD_HPP

#include <simd>
#include <span>
#include "matrix_multiplier.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Simd> {
    template<typename LHS, typename RHS>
    static auto multiply(const LHS& lhs, const RHS& rhs) {
        using LhsSimd = std::simd::vec<typename LHS::value_type>;
        using RhsSimd = std::simd::vec<typename RHS::value_type>;
        using LhsRange = std::span<const typename LHS::value_type, LhsSimd::size()>;
        using RhsRange = std::span<const typename RHS::value_type, RhsSimd::size()>;
        using ResultType = Matrix<decltype(lhs(0, 0) * rhs(0, 0)), LHS::rows, RHS::columns, MultiplicationPolicy::Simd>;
        ResultType result{};
        const auto rhsT = rhs.transpose();
        for (size_t i = 0; i < LHS::rows; ++i) {
            auto lhsRow = lhs.getRow(i);
            for (size_t j = 0; j < RHS::columns; ++j) {
                auto rhsRow = rhsT.getRow(j);

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
