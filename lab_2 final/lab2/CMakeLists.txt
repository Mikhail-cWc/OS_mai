set(CMAKE_CXX_STANDARD 14)

add_executable(child1
	src/child1.cpp
)

target_include_directories(child1 PRIVATE include)

add_executable(child2
	src/child2.cpp
)
target_include_directories(child2 PRIVATE include)

add_executable(lab2
	main.cpp
	src/parent.cpp
	include/utils.h src/utils.cpp
	)

target_include_directories(lab2 PRIVATE include)

add_dependencies(lab2 child1 child2)