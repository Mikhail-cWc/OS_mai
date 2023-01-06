cmake_minimum_required(VERSION 3.4.0)

project(lab6 CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(calculation_node
	src/server.cpp
	include/topology.h
	include/zmq_functions.h
)

add_executable(control_node
	src/client.cpp
	include/topology.h
	include/zmq_functions.h
)

target_include_directories(calculation_node PUBLIC include)
target_include_directories(control_node PUBLIC include)
target_link_libraries(control_node /usr/lib/x86_64-linux-gnu/libzmq.so)
target_link_libraries(calculation_node /usr/lib/x86_64-linux-gnu/libzmq.so)

add_dependencies(control_node calculation_node)