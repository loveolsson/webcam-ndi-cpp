file (GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${ProjectName}
    ${SOURCES}
    ${ALL_RESOURCES}
)

find_library(NDI_LIBS REQUIRED NAMES libndi libndi.4.dylib HINTS ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64)
include_directories ( ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/include )

find_package( OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/3rdParty/opencv-install/ )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories( ${CMAKE_SOURCE_DIR}/submodules/cpp-httplib )
include_directories( ${CMAKE_SOURCE_DIR}/submodules/incbin )
include_directories( ${CMAKE_SOURCE_DIR}/src )

target_link_libraries(${ProjectName}
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64/libndi.4.dylib
    ${OpenCV_LIBS}
    ${NDI_LIBS}
) 
