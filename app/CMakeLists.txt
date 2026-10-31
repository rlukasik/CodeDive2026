cmake_minimum_required(VERSION 4.3)

project(Mac)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)

FetchContent_MakeAvailable(googlebenchmark)

add_subdirectory(matrix)
add_subdirectory(matrix_cmp)
add_subdirectory(matrix_multiplier)

add_executable(mac
    main.cpp
)

target_link_libraries(mac PRIVATE iomatrix matrix matrix_cmp matrix_multiplier)
set_target_properties(mac PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(mac PRIVATE
    -O3
    -march=native
    -ffast-math
    # -g
    # -fsanitize=address
)

target_link_options(mac PRIVATE
    # -fsanitize=address
)

add_executable(unit_tests
    tests/matrix_multiplier_simd_test.cpp
    tests/matrix_multiplier_pretransposed_test.cpp
    tests/matrix_multiplier_scalar_test.cpp
)

target_link_libraries(unit_tests PRIVATE
    iomatrix
    matrix
    matrix_cmp
    matrix_multiplier
    GTest::gtest_main
)

target_compile_options(unit_tests PRIVATE
    -O3
    -march=native
    -ffast-math
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

add_executable(matrix_bench
    benchmarks/matrix_multiplier_simd_benchmark.cpp
    benchmarks/matrix_multiplier_pretransposed_benchmark.cpp
    benchmarks/matrix_multiplier_scalar_benchmark.cpp
)

target_link_libraries(matrix_bench PRIVATE
    iomatrix
    matrix
    matrix_multiplier
    benchmark::benchmark_main
)

target_compile_options(matrix_bench PRIVATE
    -O3
    -march=native
    -ffast-math
)
