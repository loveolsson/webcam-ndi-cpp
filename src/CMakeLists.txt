file (GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.h
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
include_directories( ${CMAKE_SOURCE_DIR}/resources/static )
include_directories( ${CMAKE_SOURCE_DIR}/src )

target_link_libraries(${ProjectName}
    ${OpenCV_LIBS}
    ${NDI_LIBS}
    nlohmann_json::nlohmann_json
) 