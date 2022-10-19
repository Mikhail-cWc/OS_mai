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

    constexpr int inputSize = 8;
    constexpr int outputSize = 4;

    std::array<const char *, inputSize> input = {
        "1234",
        "032",
        "12345",
        "123456",
        "987654321",
        "9463",
        "337546",
        "123"};

    std::array<int, outputSize> expectedOutput1 = {
        230, 54321, 123456789, 321};

    std::array<int, outputSize> expectedOutput2 = {
        4321, 654321, 3649, 645733};

    {
        std::ofstream inFile(fileWithInput);

        inFile << fileWithOutput1 << '\n';
        inFile << fileWithOutput2 << '\n';

        for (const auto &line : input)
        {
            inFile << line << '\n';
        }
    };

    std::ifstream inFILE(fileWithInput);
    std::istream &infile = inFILE;
    ParentRoutine(infile);

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
    outFile2.close();
    outFile1.close();
    inFILE.close();
    remove(fileWithInput);
    remove(fileWithOutput2);
    remove(fileWithOutput1);
}