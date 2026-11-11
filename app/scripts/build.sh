#!/bin/bash

cd ../_build
rm -rf *
cmake ..
CURRENT_DATETIME=$(date +%d%m%Y_%H%M%S)
cmake --build . --clean-first 2> ../output/build_results/build_result_${CURRENT_DATETIME}.txt
cd ../scripts
