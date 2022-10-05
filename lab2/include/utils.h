#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>
#include <algorithm>

#define BUFSIZE 4096

void WriteToPipe(HANDLE &g_hChildStd_IN_Wr, HANDLE &g_hChildStd_IN_Wr_2, std::string inFileName);
void ReadFromPipe1(HANDLE &g_hChildStd_OUT_Rd, HANDLE g_hOutputFile1);
void ReadFromPipe2(HANDLE &g_hChildStd_OUT_Rd_2, HANDLE g_hOutputFile2);
int ParentRoutine(std::string inFileName, std::string outFileName1 ,std::string outFileName2);
void CreateChildProcess(HANDLE ChildStd_OUT_Wr, HANDLE ChildStd_IN_Rd, std::string child);
#endif // INC_1_UTILS_H