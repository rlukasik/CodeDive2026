#ifndef MATRIX_MULTIPLIER_SIMD_HPP
#define MATRIX_MULTIPLIER_SIMD_HPP

#include <simd>
#include <span>

#include "matrix.hpp"
#include "matrix_multiplier_fwd.hpp"
#include "matrix_transposed.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Simd> {
    template<typename LHS, typename RHSType, std::size_t RHSRows, std::size_t RHSColumns>
    static auto multiply(
        const LHS& lhs,
        const MatrixTransposed<RHSType, RHSRows, RHSColumns>& rhsT
    ) {
        static_assert(
            LHS::columns == RHSRows,
            "LHS columns must match the original RHS rows."
        );

        using LhsSimd = std::simd::vec<typename LHS::value_type>;
        using RhsTSimd = std::simd::vec<RHSType>;

        static_assert(
            LhsSimd::size() == RhsTSimd::size(),
            "SIMD vector sizes must match."
        );

        using LhsRange = std::span<const typename LHS::value_type, LhsSimd::size()>;
        using RhsTRange = std::span<const RHSType, RhsTSimd::size()>;
        using ResultType = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), LHS::rows, RHSColumns>;
        ResultType result{};
        for (std::size_t i = 0; i < LHS::rows; ++i) {
            auto lhsRow = lhs.getRow(i);
            for (std::size_t j = 0; j < RHSColumns; ++j) {
                auto rhsTRow = rhsT.getRow(j);

                auto sum = typename ResultType::value_type{};
                std::size_t k = 0;
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
