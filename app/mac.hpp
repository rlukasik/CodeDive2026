#ifndef MAC_HPP
#define MAC_HPP

#include "matrix.hpp"
#include "matrix_multiplier.hpp"

template<typename LHS, typename RHS>
auto operator*(const LHS& lhs, const RHS& rhs) {
    static_assert(LHS::columns == RHS::rows, "Matrix dimensions do not match for multiplication.");

    return MatrixMultiplier<LHS::multiplicationPolicy>::multiply(lhs, rhs);
}

#endif // MAC_HPP
