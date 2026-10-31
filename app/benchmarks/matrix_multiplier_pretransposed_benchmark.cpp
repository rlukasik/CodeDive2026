#include <benchmark/benchmark.h>

#include <fstream>

#include "iomatrix.hpp"
#include "matrix.hpp"
#include "matrix_multiplier_pretransposed.hpp"
#include "matrix_transposed.hpp"

static void BM_Double_Pretransposed(benchmark::State& state)
{
    using LhsDouble = Matrix<double, 1024, 2048>;
    using RhsDoubleT = MatrixTransposed<double, 2048, 3072>;

    static LhsDouble lhs{};
    static RhsDoubleT rhsT{};

    std::ifstream file1024x2048("../input/matrix_1024x2048.csv");
    std::ifstream file2048x3072("../input/matrix_2048x3072.csv");

    file1024x2048 >> lhs;
    file2048x3072 >> rhsT;

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Double_Pretransposed);

static void BM_Int_Pretransposed(benchmark::State& state)
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
            MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Int_Pretransposed);
