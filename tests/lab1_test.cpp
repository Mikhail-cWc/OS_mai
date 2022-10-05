#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <cstdio>
#include <memory>
//#include <filesystem>
// namespace fs = std::filesystem;

extern "C++"
{
#include <utils.h>
}

TEST(FirstLabTests, SimpleTest)
{
    const char *fileWithInput = "C:\\project\\OS_mai\\build\\tests\\input.txt";
    const char *fileWithOutput1 = "C:\\project\\OS_mai\\build\\tests\\output1.txt";
    const char *fileWithOutput2 = "C:\\project\\OS_mai\\build\\tests\\output2.txt";

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
        123456789, 54321, 230};

    std::array<int, outputSize> expectedOutput2 = {
        3649, 654321, 4321};

    {
        std::ofstream inFile(fileWithInput);

        //    inFile << fileWithOutput << '\n';

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

    ParentRoutine(fileWithInput, fileWithOutput1, fileWithOutput2);

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
    /*

       auto removeIfExists = [](const char *path)
        {
            if (fs::exists(path))
            {
                fs::remove(path);
            }
        };

        removeIfExists(fileWithInput);
        removeIfExists(fileWithOutput1);
        removeIfExists(fileWithOutput2); */
}