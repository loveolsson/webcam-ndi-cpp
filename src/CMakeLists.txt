add_executable(${ProjectName}
    Main.cpp
)

target_link_libraries(${ProjectName}
    ${CMAKE_SOURCE_DIR}/3rdParty/NDI-SDK/lib/x64/libndi.4.dylib
) 
