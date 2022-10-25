#include "include\\lab3.h"

int main()
{
    srand(time(0));
    int NumberOfThreads, n, m, k;

    std::cout << "Введите количество потоков, N, M, K:\n";
    std::cin >> NumberOfThreads;
    std::cin >> n;
    std::cin >> m;
    std::cin >> k;
    if (n <= 0 || m <= 0 || k <= 0 || NumberOfThreads <= 0)
    {
        std::cout << "ERROR CREATED COMPLEX MATRIX or NUM OF THREADS\n";
        return -1;
    }

    TComplexMatrix matr_1(n, std::vector<std::complex<double>>(m, 0));
    TComplexMatrix matr_2(m, std::vector<std::complex<double>>(k, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matr_1[i][j] = std::complex<double>(rand() % 15, rand() % 30);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            std::cout << matr_1[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++)
            matr_2[i][j] = std::complex<double>(rand() % 15, rand() % 30);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            std::cout << matr_2[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    double avg = 0;
    auto start = std::chrono::high_resolution_clock::now();

    auto res = Parallelization(matr_1, matr_2, NumberOfThreads);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            std::cout << res[i][j] << " ";
        std::cout << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    printf("Время выполнения программы(миллисекунды): %f\n", avg);
    system("PAUSE");
    return 0;
}