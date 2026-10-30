add_library(matrix_multiplier INTERFACE)

target_include_directories(matrix_multiplier
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(matrix_multiplier
    INTERFACE
        matrix
)