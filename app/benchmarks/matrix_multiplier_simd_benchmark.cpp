#include <benchmark/benchmark.h>

#include "benchmark_matrices.hpp"
#include "matrix_multiplier_simd.hpp"

static void BM_Double_Simd(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<double>();
    auto result = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), decltype(lhs)::rows, decltype(rhsT)::rows>{};

    for (auto _ : state) {
        MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT, result);

        benchmark::DoNotOptimize(result);
    }
    constexpr double operations_per_iteration = 2.0 * static_cast<double>(lhs.rows) * static_cast<double>(lhs.columns) * static_cast<double>(rhsT.rows);
    state.counters["GFLOP/s"] = benchmark::Counter(
        operations_per_iteration / 1e9,
        benchmark::Counter::kIsIterationInvariantRate
    );
}

BENCHMARK(BM_Double_Simd);

static void BM_Int_Simd(benchmark::State& state)
{
    const auto& [lhs, rhsT] = benchmark_matrices<int>();
    auto result = Matrix<decltype(lhs(0, 0) * rhsT(0, 0)), decltype(lhs)::rows, decltype(rhsT)::rows>{};

    for (auto _ : state) {
        MatrixMultiplier<MultiplicationPolicy::Simd>::multiply(lhs, rhsT, result);

        benchmark::DoNotOptimize(result);
    }
    constexpr double operations_per_iteration = 2.0 * static_cast<double>(lhs.rows) * static_cast<double>(lhs.columns) * static_cast<double>(rhsT.rows);
    state.counters["GOp/s"] = benchmark::Counter(
        operations_per_iteration / 1e9,
        benchmark::Counter::kIsIterationInvariantRate
    );
}

BENCHMARK(BM_Int_Simd);
