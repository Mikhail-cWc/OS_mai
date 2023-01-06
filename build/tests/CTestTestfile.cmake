# CMake generated Testfile for 
# Source directory: /home/nucyc/OS_mai/tests
# Build directory: /home/nucyc/OS_mai/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[lab1_test]=] "lab1_test")
set_tests_properties([=[lab1_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/nucyc/OS_mai/tests/CMakeLists.txt;23;add_test;/home/nucyc/OS_mai/tests/CMakeLists.txt;0;")
add_test([=[lab3_test]=] "lab3_test")
set_tests_properties([=[lab3_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/nucyc/OS_mai/tests/CMakeLists.txt;31;add_test;/home/nucyc/OS_mai/tests/CMakeLists.txt;0;")
add_test([=[lab5_test]=] "lab5_test")
set_tests_properties([=[lab5_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/nucyc/OS_mai/tests/CMakeLists.txt;40;add_test;/home/nucyc/OS_mai/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
