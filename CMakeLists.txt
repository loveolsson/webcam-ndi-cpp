cmake_minimum_required (VERSION 3.2)

set(ProjectName WebcamNDI)
project(${ProjectName})

set (CMAKE_CXX_STANDARD 17)

include_directories (
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/include
    ${CMAKE_SOURCE_DIR}/3rdParty/opencv-build/include
)

link_directories (
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64
    ${CMAKE_SOURCE_DIR}/3rdParty/opencv/lib
)

add_subdirectory (src)

set_target_properties(${ProjectName}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
