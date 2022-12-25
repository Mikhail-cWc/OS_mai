
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# LAB 2 tests
add_executable(lab1_test lab2_test.cpp ../lab2/src/parent.cpp ../lab2/include/parent.h
        ../lab2/src/utils.cpp ../lab2/include/utils.h)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab2/include)

add_test(lab1_test lab1_test)

# LAB 3 tests
add_executable(lab3_test lab3_test.cpp ../lab3/include/lab3.h ../lab3/src/lab3.cpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)

# LAB 5 tests
add_executable(lab5_test lab5_test.cpp ../lab5/include/utils.h ../lab5/src/programm1.cpp ../lab5/include/MathUnit.h ../lab5/src/programm2.cpp)

target_link_libraries(lab5_test C:/OS_mai/lab5/lib/libmath.dll GTest::GTest)

#target_link_libraries(lab5_test PRIVATE GTest::GTest)
target_include_directories(lab5_test PRIVATE ../lab5/include)

add_test(lab5_test lab5_test)