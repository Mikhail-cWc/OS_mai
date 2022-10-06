cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/x86_64-w64-mingw32-g++.exe") 
set(CMAKE_C_COMPILER "C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/x86_64-w64-mingw32-gcc.exe")

project(OS_LABS C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX) 
else()
    add_compile_options(-Wall -lstdc++fs)
endif()

add_subdirectory(lab2)
add_subdirectory(tests)
