set(CMAKE_CXX_STANDARD 14)

add_executable(A
	A.cpp
)
add_executable(B
	B.cpp
)
add_executable(C
	C.cpp
)
add_executable(kp
	main.cpp
	)
add_dependencies(kp A B C)