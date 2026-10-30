add_library(matrix INTERFACE)

add_subdirectory(iomatrix)

target_include_directories(matrix
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
