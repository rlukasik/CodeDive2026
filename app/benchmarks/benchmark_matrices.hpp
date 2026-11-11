#ifndef BENCHMARK_MATRICES_HPP
#define BENCHMARK_MATRICES_HPP

#include <iostream>
#include <fstream>

#include "iomatrix.hpp"
#include "matrix.hpp"
#include "matrix_transposed.hpp"

template<typename T>
const auto& benchmark_matrices()
{
    using Lhs = Matrix<T, 1024, 2048>;
    using RhsT = MatrixTransposed<T, 2048, 3072>;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    static const auto matrices = [] {
        Lhs lhs{};
        RhsT rhsT{};

        std::ifstream lhsFile("../input/matrix_1024x2048.csv");
        std::ifstream rhsFile("../input/matrix_2048x3072.csv");

        if (!lhsFile || !rhsFile) {
            throw std::runtime_error("Could not open benchmark input CSV files");
        }
        if (!(lhsFile >> lhs) || !(rhsFile >> rhsT)) {
            throw std::runtime_error("Could not read benchmark input matrices");
        }

        return std::pair{std::move(lhs), std::move(rhsT)};
    }();

    return matrices;
}

#endif // BENCHMARK_MATRICES_HPP