#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>
#include <complex>
#include <windows.h>
#include <process.h>
#include <ctime>
#include <iostream>

using namespace std;
using ComplexMatrix = vector<vector<complex<double>>>;

typedef struct data
{
	int q, r;
	ComplexMatrix right;
	ComplexMatrix left;
	ComplexMatrix res;
	vector<int> from, to;
} * PMYDATA, MYDATA;

DWORD WINAPI MatrixMultiplication(LPVOID param);

ComplexMatrix Parallelization(ComplexMatrix left, ComplexMatrix right, int threads);

#endif // OS_LABS_LAB3_H