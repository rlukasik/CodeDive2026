#include <benchmark/benchmark.h>

#include "benchmark_matrices.hpp"
#include "matrix_multiplier_simd.hpp"

static void BM_Double_Simd(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<double>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Double_Simd);

static void BM_Int_Simd(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<int>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Int_Simd);
