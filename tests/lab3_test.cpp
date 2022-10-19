#include <gtest/gtest.h>

#include "lab3.h"

#include <chrono>

namespace
{
    ComplexMatrix GenerateMatrix(int n, int m)
    {
        ComplexMatrix result(n, vector<complex<double>>(m));

        srand(time(nullptr));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                result[i][j] = complex<double>(rand() % 100, rand() % 50);
            }
        }

        return result;
    }
}

bool operator==(const ComplexMatrix &lhs, const ComplexMatrix &rhs)
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
    ComplexMatrix matr_1 = {{complex<double>(3, 0)}};
    ComplexMatrix matr_2 = {{complex<double>(3, 0)}};
    ComplexMatrix res = {{complex<double>(9, 0)}};
    EXPECT_EQ(Parallelization(matr_1, matr_2, 1), res);

    ComplexMatrix matr_3 = {{complex<double>(3, 5), complex<double>(2, 7)}, {complex<double>(8, 2), complex<double>(4, 2)}};
    ComplexMatrix matr_4 = {{complex<double>(1, 2), complex<double>(3, 4)}, {complex<double>(5, 6), complex<double>(7, 8)}};
    ComplexMatrix res2 = {{complex<double>(-39, 58), complex<double>(-53, 92)}, {complex<double>(12, 52), complex<double>(28, 84)}};
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
    performTestForGivenSize(10, 10, 10, 2);
    performTestForGivenSize(100, 100, 100, 3);
    performTestForGivenSize(600, 600, 600, 4);
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
            avg += chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    cout << "Avg time for 1 thread: " << singleThread << '\n';
    cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}