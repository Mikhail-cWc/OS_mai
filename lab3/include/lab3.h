#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>
#include <complex>
#include <windows.h>
#include <process.h>
#include <ctime>
#include <iostream>
#include <chrono>

using TComplexMatrix = std::vector<std::vector<std::complex<double>>>;

struct MYDATA
{

	TComplexMatrix right;
	TComplexMatrix left;
	TComplexMatrix res;
	std::vector<int> from, to;
};

DWORD WINAPI MatrixMultiplication(LPVOID param);

TComplexMatrix Parallelization(TComplexMatrix left, TComplexMatrix right, int threads);

#endif // OS_LABS_LAB3_H