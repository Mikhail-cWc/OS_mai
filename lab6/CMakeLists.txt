cmake_minimum_required(VERSION 3.4.0)

project(lab6 CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(counting
	src/counting.cpp
	include/topology.h
	include/zmq_functions.h
)

add_executable(control
	src/control.cpp
	include/topology.h
	include/zmq_functions.h
)

target_include_directories(counting PUBLIC include)
target_include_directories(control PUBLIC include)
target_link_libraries(control /usr/lib/x86_64-linux-gnu/libzmq.so)
target_link_libraries(counting /usr/lib/x86_64-linux-gnu/libzmq.so)

add_dependencies(control counting)