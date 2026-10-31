#include <benchmark/benchmark.h>

#include "benchmark_matrices.hpp"
#include "matrix_multiplier_scalar.hpp"

static void BM_Double_Scalar(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<double>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Double_Scalar);

static void BM_Int_Scalar(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<int>();

    for (auto _ : state) {
        auto result =
            MatrixMultiplier<MultiplicationPolicy::Scalar>::multiply(lhs, rhsT);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Int_Scalar);
