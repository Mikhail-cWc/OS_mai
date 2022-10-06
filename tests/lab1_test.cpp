#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <cstdio>
#include <memory>
#include "parent.h"

TEST(FirstLabTests, SimpleTest)
{
    const char *fileWithInput = "input.txt";
    const char *fileWithOutput1 = "output1.txt";
    const char *fileWithOutput2 = "output2.txt";

    constexpr int inputSize = 6;
    constexpr int outputSize = 3;

    std::array<const char *, inputSize> input = {
        "1234",
        "032",
        "12345",
        "123456",
        "987654321",
        "9463"};

    std::array<int, outputSize> expectedOutput1 = {
        230, 54321, 123456789};

    std::array<int, outputSize> expectedOutput2 = {
        4321, 654321, 3649};

    {
        std::ofstream inFile(fileWithInput);

        inFile << fileWithOutput1 << '\n';
        inFile << fileWithOutput2 << '\n';

        for (const auto &line : input)
        {
            inFile << line << '\n';
        }
    }

    auto deleter = [](FILE *file)
    {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    ParentRoutine(fileWithInput);

    std::ifstream outFile1(fileWithOutput1);

    ASSERT_TRUE(outFile1.good());

    std::ifstream outFile2(fileWithOutput2);

    ASSERT_TRUE(outFile2.good());

    int result;

    for (int i : expectedOutput1)
    {
        outFile1 >> result;
        EXPECT_EQ(result, i);
    }

    result = -1;

    for (int i : expectedOutput2)
    {
        outFile2 >> result;
        EXPECT_EQ(result, i);
    }
}