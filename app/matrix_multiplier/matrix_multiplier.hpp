#ifndef MATRIX_MULTIPLIER_HPP
#define MATRIX_MULTIPLIER_HPP

#include "matrix_policy.hpp"

template<MultiplicationPolicy Policy>
struct MatrixMultiplier;

#include "matrix_multiplier_scalar.hpp"
#include "matrix_multiplier_with_transpose.hpp"
#include "matrix_multiplier_simd.hpp"

#endif // MATRIX_MULTIPLIER_HPP
