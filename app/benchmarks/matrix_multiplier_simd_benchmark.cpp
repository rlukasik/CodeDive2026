#include <benchmark/benchmark.h>

#include <fstream>

#include "iomatrix.hpp"
#include "matrix.hpp"
#include "matrix_multiplier_simd.hpp"
#include "matrix_transposed.hpp"

using Lhs = Matrix<double, 1024, 2048>;
using RhsT = MatrixTransposed<double, 2048, 3072>;

static void BM_Double_Simd(benchmark::State& state)
{
    static Lhs lhs{};
    static RhsT rhsT{};

    std::ifstream file1024x2048("../input/matrix_1024x2048.csv");
    std::ifstream file2048x3072("../input/matrix_2048x3072.csv");

    file1024x2048 >> lhs;
    file2048x3072 >> rhsT;

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Double_Simd);

static void BM_Int_Simd(benchmark::State& state)
{
    using LhsInt = Matrix<int, 1024, 2048>;
    using RhsIntT = MatrixTransposed<int, 2048, 3072>;

    static LhsInt lhs{};
    static RhsIntT rhsT{};

    std::ifstream file1024x2048("../input/matrix_1024x2048.csv");
    std::ifstream file2048x3072("../input/matrix_2048x3072.csv");

    file1024x2048 >> lhs;
    file2048x3072 >> rhsT;

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Int_Simd);
