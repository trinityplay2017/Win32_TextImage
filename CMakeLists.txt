cmake_minimum_required(VERSION 3.16)
project(Win32_TextImage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Win32_TextImage src/main.cpp)

if(WIN32)
    target_compile_definitions(Win32_TextImage PRIVATE UNICODE _UNICODE)
    # Force console subsystem
    set_target_properties(Win32_TextImage PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    target_link_libraries(Win32_TextImage PRIVATE
        WindowsApp
        oleaut32
        ole32
        user32
    )
endif()
