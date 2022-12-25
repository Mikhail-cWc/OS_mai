set(CMAKE_CXX_STANDARD 14)

add_executable(child3
	src/child1.cpp)

target_include_directories(child3 PRIVATE include)

add_executable(child4
	src/child2.cpp)
target_include_directories(child4 PRIVATE include)

add_executable(lab4
	main.cpp
	src/parent.cpp
	include/utils.h
	src/utils.cpp)

target_include_directories(lab4 PRIVATE include)

add_dependencies(lab4 child3 child4)