#ifndef MATRIX_MULTIPLIER_SIMD_HPP
#define MATRIX_MULTIPLIER_SIMD_HPP

#include <simd>
#include <span>
#include <type_traits>

#include "matrix.hpp"
#include "matrix_multiplier_fwd.hpp"
#include "matrix_transposed.hpp"

template<>
struct MatrixMultiplier<MultiplicationPolicy::Simd> {
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

        static_assert(
            std::is_same_v<typename LHS::value_type, RHSTType>,
            "Value types must match for SIMD multiplication."
        );

        using LhsSimd = std::simd::vec<typename LHS::value_type>;
        using RhsTSimd = std::simd::vec<RHSTType>;
        using LhsRange = std::span<const typename LHS::value_type, LhsSimd::size()>;
        using RhsTRange = std::span<const RHSTType, RhsTSimd::size()>;
        for (std::size_t i = 0; i < LHS::rows; ++i) {
            auto lhsRow = lhs.getRow(i);
            for (std::size_t j = 0; j < RHSTRows; ++j) {
                auto rhsTRow = rhsT.getRow(j);

                using Result = std::remove_cvref_t<decltype(result)>;
                auto sum = typename Result::value_type{};
                LhsSimd vectorSum{};
                std::size_t k = 0;
                for (; k + LhsSimd::size() <= LHS::columns; k += LhsSimd::size()) {
                    LhsRange lhsRange{lhsRow + k, LhsSimd::size()};
                    RhsTRange rhsTRange{rhsTRow + k, RhsTSimd::size()};
                    LhsSimd lhsVec{lhsRange};
                    RhsTSimd rhsTVec{rhsTRange};
                    vectorSum += lhsVec * rhsTVec;
                }

                sum = std::simd::reduce(vectorSum);

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
