#ifndef MATRIX_POLICY_HPP
#define MATRIX_POLICY_HPP

enum class MultiplicationPolicy {
    Scalar,
    WithTranspose,
    Simd
};

#endif // MATRIX_POLICY_HPP
