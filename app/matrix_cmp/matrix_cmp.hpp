#ifndef MATRIX_CMP_HPP
#define MATRIX_CMP_HPP

#include <algorithm>
#include <cstddef>
#include <cmath>
#include <type_traits>

template<typename LHS, typename RHS>
bool matrix_cmp(const LHS& lhs, const RHS& rhs) {
    static_assert(
        LHS::rows == RHS::rows &&
        LHS::columns == RHS::columns &&
        std::is_same_v<typename LHS::value_type, typename RHS::value_type>,
        "Matrices must have the same dimensions and value types for comparison."
    );

    static constexpr double epsilon = 1e-6; // Tolerance for floating-point comparison
    static constexpr double relative_epsilon = 1e-5; // Relative tolerance for floating-point comparison

    for (std::size_t row = 0; row < LHS::rows; ++row) {
        for (std::size_t col = 0; col < LHS::columns; ++col) {
            if constexpr (std::is_floating_point_v<typename LHS::value_type>) {
                const double lhs_value = static_cast<double>(lhs(row, col));
                const double rhs_value = static_cast<double>(rhs(row, col));
                if (lhs_value == rhs_value) {
                    continue; // Exact match
                }
                if (!std::isfinite(lhs_value) || !std::isfinite(rhs_value)) {
                    return false; // One of the values is NaN or infinity
                }
                const double abs_diff = std::abs(lhs_value - rhs_value);
                const double max_abs = std::max(std::abs(lhs_value), std::abs(rhs_value));
                if (abs_diff > epsilon + relative_epsilon * max_abs) {
                    return false;
                }
            } else {
                if (lhs(row, col) != rhs(row, col)) {
                    return false;
                }
            }
        }
    }
    return true;
}

#endif // MATRIX_CMP_HPP
