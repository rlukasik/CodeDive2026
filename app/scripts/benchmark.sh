#!/bin/bash

cd ../_build
CURRENT_DATETIME=$(date +%d%m%Y_%H%M%S)
./matrix_bench   --benchmark_repetitions=20   --benchmark_out=../output/benchmark_results/benchmark_result_${CURRENT_DATETIME}.json   --benchmark_out_format=json --benchmark_counters_tabular=true
cd ../scripts
