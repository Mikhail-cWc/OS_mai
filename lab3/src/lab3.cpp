#include "lab3.h"

PMYDATA mydata;
DWORD WINAPI MatrixMultiplication(LPVOID param)
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

ComplexMatrix Parallelization(ComplexMatrix left, ComplexMatrix right, int threads)
{
    mydata = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                sizeof(MYDATA));
    vector<int> to(threads, 0);
    vector<int> from(threads, 0);
    ComplexMatrix res(left.size(), vector<complex<double>>(right[0].size(), 0));
    mydata->to = to;
    mydata->from = from;
    mydata->left = left;
    mydata->right = right;
    mydata->res = res;
    mydata->q = mydata->left.size() / threads;
    mydata->r = mydata->left.size() % threads;
    HANDLE hThreads[threads];
    LPDWORD id;
    int noms[threads];

    for (int i = 0; i < threads; i++)
    {
        mydata->to[i] = mydata->from[i] + mydata->q + (i < mydata->r ? 1 : 0);
        noms[i] = i;
        hThreads[i] = CreateThread(NULL, 0, MatrixMultiplication, (LPVOID)(noms + i), 0, id);
        if (i < threads - 1)
            mydata->from[i + 1] = mydata->to[i];

        if (hThreads[i] == NULL)
            cout << "ERROR CREATE THREADS - " << i << endl;
    }

    WaitForMultipleObjects(threads, hThreads, TRUE, INFINITE);

    for (int i = 0; i < threads; i++)
        CloseHandle(hThreads[i]);

    ComplexMatrix result = mydata->res;

    HeapFree(GetProcessHeap(), 0, mydata);
    mydata = NULL;

    return result;
}
