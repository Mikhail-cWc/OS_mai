#include <gtest/gtest.h>

#include "lab3.h"

#include <chrono>

namespace
{
    TComplexMatrix GenerateMatrix(int n, int m)
    {
        TComplexMatrix result(n, std::vector<std::complex<double>>(m));

        srand(time(nullptr));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                result[i][j] = std::complex<double>(rand() % 100, rand() % 50);
            }
        }

        return result;
    }
}

bool operator==(const TComplexMatrix &lhs, const TComplexMatrix &rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }

    for (int i = 0; i < lhs.size(); ++i)
    {
        if (lhs[i].size() != rhs[i].size())
        {
            return false;
        }

        for (int j = 0; j < lhs[0].size(); ++j)
        {
            if (real(lhs[i][j]) != real(rhs[i][j]))
            {
                return false;
            }
            if (imag(lhs[i][j]) != imag(rhs[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

TEST(ThirdLabTests, SingleThreadYieldsCorrectResults)
{
    TComplexMatrix matr_1 = {{std::complex<double>(3, 0)}};
    TComplexMatrix matr_2 = {{std::complex<double>(3, 0)}};
    TComplexMatrix res = {{std::complex<double>(9, 0)}};
    EXPECT_EQ(Parallelization(matr_1, matr_2, 1), res);

    TComplexMatrix matr_3 = {{std::complex<double>(3, 5), std::complex<double>(2, 7)}, {std::complex<double>(8, 2), std::complex<double>(4, 2)}};
    TComplexMatrix matr_4 = {{std::complex<double>(1, 2), std::complex<double>(3, 4)}, {std::complex<double>(5, 6), std::complex<double>(7, 8)}};
    TComplexMatrix res2 = {{std::complex<double>(-39, 58), std::complex<double>(-53, 92)}, {std::complex<double>(12, 52), std::complex<double>(28, 84)}};
    EXPECT_EQ(Parallelization(matr_3, matr_4, 1), res2);
}

TEST(ThirdLabTest, ThreadConfigurations)
{
    auto performTestForGivenSize = [](int n, int m, int k, int maxThreadCount)
    {
        auto m1 = GenerateMatrix(n, m);
        auto m2 = GenerateMatrix(m, k);
        auto result = Parallelization(m1, m2, 1);

        for (int i = 1; i < maxThreadCount; ++i)
        {
            EXPECT_EQ(Parallelization(m1, m2, i), result);
        }
    };

    performTestForGivenSize(3, 3, 3, 2);
    performTestForGivenSize(10, 13, 14, 2);
    performTestForGivenSize(100, 152, 523, 3);
    performTestForGivenSize(500, 500, 500, 4);
}

TEST(ThirdLabTest, PerfomanceTest)
{
    auto getAvgTime = [](int threadCount)
    {
        auto m1 = GenerateMatrix(500, 500);
        auto m2 = GenerateMatrix(500, 500);

        constexpr int runsCount = 5;

        double avg = 0;

        for (int i = 0; i < runsCount; ++i)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            Parallelization(m1, m2, threadCount);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}