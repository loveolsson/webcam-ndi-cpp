cmake_minimum_required (VERSION 3.2)

set(ProjectName WebcamNDI)
project(${ProjectName})

set (CMAKE_CXX_STANDARD 17)

add_subdirectory (src)

set_target_properties(${ProjectName}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
