
cmake_minimum_required(VERSION 3.4.0)

project(lab5 CXX)

# Установка переменной со списком исходников
set(SOURCE_LIB lib/MathLibrary.cpp)

# Включение экспорта всех символов для создания динамической библиотеки
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Создание динамической библиотеки с именем math
add_library(math SHARED ${SOURCE_LIB})

set(CMAKE_CXX_STANDARD 14)

add_executable(lab5_2
	main.cpp
	src/programm2.cpp
	include/utils.h
)

add_executable(lab5_1
	main2.cpp
	src/programm1.cpp
	lib/MathUnit.h
	include/utils.h
)

target_include_directories(lab5_2 PUBLIC include)
target_include_directories(lab5_1 PUBLIC include)

target_link_libraries(lab5_1 C:/OS_mai/lab5/lib/libmath.dll)

add_dependencies(lab5_1 lab5_2)