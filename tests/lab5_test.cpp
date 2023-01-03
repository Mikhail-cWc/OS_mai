#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <cstdio>
#include <memory>
#include "utils.h"
#include "MathUnit.h"
#include <string>

TEST(FiveLabTests, ProgrammFirstTest)
{
    const char *fileWithInput = "input.txt";
    constexpr int inputSize = 10;
    std::array<const char *, inputSize> input = {
        "1 10",
        "1 100",
        "2 1",
        "2 543",
        "0",
        "1 10",
        "1 100",
        "2 1",
        "2 543",
        "3 343"};

    {
        std::ofstream inFile(fileWithInput);
        for (const auto &line : input)
        {
            inFile << line << '\n';
        }
    };
    std::ifstream inFILE(fileWithInput);
    std::istream &infile = inFILE;

    const char *fileWithOutput1 = "output1.txt";
    constexpr int outputSize = 10;
    std::array<const char *, outputSize> expectedOutput1 = {
        "3.041839838027954",
        "3.131592750549316",
        "2.000000000000000",
        "2.718281984329224",
        "invalid_command",
        "3.041839838027954",
        "3.131592750549316",
        "2.000000000000000",
        "2.718281984329224",
        "invalid_command"};

    programm1(infile, fileWithOutput1);

    std::ifstream outFile1(fileWithOutput1);

    ASSERT_TRUE(outFile1.good());

    std::string result;

    for (const auto &i : expectedOutput1)
    {
        outFile1 >> result;
        EXPECT_EQ(result, i);
    }
    remove(fileWithInput);
    remove(fileWithOutput1);
}

TEST(FiveLabTests, ProgrammSecondTest)
{
    const char *fileWithInput = "input.txt";
    constexpr int inputSize = 10;
    std::array<const char *, inputSize> input = {
        "1 10",
        "1 100",
        "2 1",
        "2 543",
        "0",
        "1 10",
        "1 100",
        "2 1",
        "2 543",
        "3 343"};

    {
        std::ofstream inFile(fileWithInput);
        for (const auto &line : input)
        {
            inFile << line << '\n';
        }
    };
    std::ifstream inFILE(fileWithInput);
    std::istream &infile = inFILE;

    const char *fileWithOutput2 = "output2.txt";
    constexpr int outputSize = 10;
    std::array<const char *, outputSize> expectedOutput2 = {
        "3.041839838027954",
        "3.131592750549316",
        "2.000000000000000",
        "2.718281984329224",
        "Swithing_the_implementation_of_mathematical_function",
        "3.141520261764526",
        "3.141591787338257",
        "2.000000000000000",
        "2.718281984329224",
        "invalid_command"};

    programm2(infile, fileWithOutput2);

    std::ifstream outFile2(fileWithOutput2);

    ASSERT_TRUE(outFile2.good());

    std::string result = "";

    for (const auto &i : expectedOutput2)
    {
        outFile2 >> result;
        EXPECT_EQ(result, i);
    }
    remove(fileWithInput);
    remove(fileWithOutput2);
}
