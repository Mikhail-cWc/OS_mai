
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        GIT_TAG        release-1.12.1
)


FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# LAB 1 tests
add_executable(lab1_test lab1_test.cpp ../lab2/src/parent.cpp ../lab2/include/parent.h
        ../lab2/src/utils.cpp ../lab2/include/utils.h)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab2/include)

add_test(lab1_test lab1_test)