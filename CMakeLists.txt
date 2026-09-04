cmake_minimum_required(VERSION 3.16)
project(Win32_TextImage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable C++/WinRT
add_executable(Win32_TextImage src/main.cpp)

# Windows specific
if(WIN32)
    target_compile_definitions(Win32_TextImage PRIVATE UNICODE _UNICODE)
    # Link Windows Runtime support
    target_link_libraries(Win32_TextImage PRIVATE WindowsApp)
endif()

# Note: For full C++/WinRT support in CMake you may need:
# - cppwinrt tool or Microsoft.Windows.CppWinRT NuGet
# - Or use Visual Studio generator and set /ZW if using older projection
