#include "include\\lab3.h"

int main()
{
    srand(time(0));
    int NumberOfThreads = 2;
    int n = 10;
    int m = 10;
    int k = 10;

    ComplexMatrix matr_1(n, vector<complex<double>>(m, 0));
    ComplexMatrix matr_2(m, vector<complex<double>>(k, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matr_1[i][j] = complex<double>(rand() % 15, rand() % 30);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << matr_1[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++)
            matr_2[i][j] = complex<double>(rand() % 15, rand() % 30);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << matr_2[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    clock_t start, end;
    start = clock();

    auto res = Parallelization(matr_1, matr_2, NumberOfThreads);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            cout << res[i][j] << " ";
        cout << endl;
    }
    end = clock() - start;
    printf("Время выполнения программы: %f\n", end / (double)CLOCKS_PER_SEC);
}