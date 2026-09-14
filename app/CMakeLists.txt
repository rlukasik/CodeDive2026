cmake_minimum_required(VERSION 4.3)

project(Mac)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(matrix_multiplier)

add_executable(mac
    main.cpp
)

target_link_libraries(mac PRIVATE matrix_multiplier)
set_target_properties(mac PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(mac PRIVATE
    -O3
    -march=native
    -g
    -fsanitize=address
)

target_link_options(mac PRIVATE
    -fsanitize=address
)
