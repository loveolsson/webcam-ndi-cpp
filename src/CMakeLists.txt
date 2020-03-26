file (GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${ProjectName}
    ${SOURCES}
)

include_directories (
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/include
)

find_library(NDI_LIBS REQUIRED NAMES libndi libndi.4.dylib HINTS ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64)

find_package( OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/3rdParty/opencv-install/ )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries(${ProjectName}
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64/libndi.4.dylib
    ${OpenCV_LIBS}
    ${NDI_LIBS}
) 
