#include <benchmark/benchmark.h>

#include "benchmark_matrices.hpp"
#include "matrix_multiplier_pretransposed.hpp"

static void BM_Double_Pretransposed(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<double>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Double_Pretransposed);

static void BM_Int_Pretransposed(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<int>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Pretransposed>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Int_Pretransposed);
