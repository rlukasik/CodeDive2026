add_library(iomatrix INTERFACE)

target_include_directories(iomatrix
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(iomatrix
    INTERFACE
        matrix
)