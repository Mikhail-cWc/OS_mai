#include "lab3.h"

MYDATA *mydata;
unsigned long WINAPI MatrixMultiplication(LPVOID param)
{
    int iNumm = *(reinterpret_cast<int *>(param));

    for (int i = mydata->from[iNumm]; i < mydata->to[iNumm]; i++)
    {
        for (int j = 0; j < mydata->res[0].size(); j++)
        {
            mydata->res[i][j] = 0;
            for (int z = 0; z < mydata->res.size(); z++)
                mydata->res[i][j] += mydata->left[i][z] * mydata->right[z][j];
        }
    }

    return 0;
}

TComplexMatrix Parallelization(TComplexMatrix left, TComplexMatrix right, int threads)
{
    mydata = (MYDATA *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                 sizeof(MYDATA));
    std::vector<int> to(threads, 0);
    std::vector<int> from(threads, 0);
    TComplexMatrix res(left.size(), std::vector<std::complex<double>>(right[0].size(), 0));
    mydata->left = left;
    mydata->right = right;
    mydata->res = res;

    // Данные переменные нужны для распределения вычислений по потокам
    int q = left.size() / threads;
    int r = left.size() % threads;
    mydata->to = to;
    mydata->from = from;

    HANDLE hThreads[threads];
    LPDWORD id;
    int noms[threads];

    for (int i = 0; i < threads; i++)
    {
        // У последнего потока будет четное кол-во строк для вычислений
        // При условии что в матрице строк нечетное кол-во
        mydata->to[i] = mydata->from[i] + q + (i < r ? 1 : 0);
        noms[i] = i;
        hThreads[i] = CreateThread(NULL, 0, MatrixMultiplication, (LPVOID)(noms + i), 0, id);
        if (i < threads - 1)
            mydata->from[i + 1] = mydata->to[i];

        if (hThreads[i] == NULL)
            std::cout << "ERROR CREATE THREADS - " << i << std::endl;
    }

    WaitForMultipleObjects(threads, hThreads, TRUE, INFINITE);

    for (int i = 0; i < threads; i++)
        CloseHandle(hThreads[i]);

   TComplexMatrix result = mydata->res;

    HeapFree(GetProcessHeap(), 0, mydata);
    mydata = NULL;

    return result;
}
