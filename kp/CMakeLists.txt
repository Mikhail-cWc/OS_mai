set(CMAKE_CXX_STANDARD 14)

add_executable(A
	src/A.cpp
	include/utils.h
		src/utils.cpp

)
target_include_directories(A PRIVATE include)

add_executable(B
	src/B.cpp
	include/utils.h
	src/utils.cpp
)
target_include_directories(B PRIVATE include)

add_executable(C
	src/C.cpp
	include/utils.h
	src/utils.cpp
)
target_include_directories(C PRIVATE include)

add_executable(kp
	main.cpp
	src/utils.cpp
	include/utils.h
	)
target_include_directories(kp PRIVATE include)

add_dependencies(kp A B C)