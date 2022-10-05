#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>
// pipe1 (child1)
HANDLE g_hChildStd_IN_Rd = NULL;	 // Cтандартный дескриптор ввода для доч. процесса
HANDLE g_hChildStd_IN_Wr = NULL;	 // Дескриптор для записи во входные данные доч. процесса(не наследуется)
HANDLE g_hChildStd_OUT_Rd = NULL; // Дескриптор для чтения из выходных данных доч. процесса(не наследуется)
HANDLE g_hChildStd_OUT_Wr = NULL; // Стандартный дескриптор вывода для доч. процесса

// pipe2 (child2)
HANDLE g_hChildStd_IN_Rd_2 = NULL;
HANDLE g_hChildStd_IN_Wr_2 = NULL;
HANDLE g_hChildStd_OUT_Rd_2 = NULL;
HANDLE g_hChildStd_OUT_Wr_2 = NULL;

std::string child1 = "C:\\project\\OS_mai\\build\\lab2\\child1.exe";
std::string child2 = "C:\\project\\OS_mai\\build\\lab2\\child2.exe";

HANDLE g_hOutputFile1 = NULL;
HANDLE g_hOutputFile2 = NULL;

#endif // OS_LABS_PARENT_H