#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>
#include <algorithm>

#define BUFSIZE 4096

void WriteToPipe(HANDLE g_hChildStd_IN_Wr, HANDLE g_hChildStd_IN_Wr_2, std::istream &inFile);
void ReadFromPipe(HANDLE g_hChildStd_OUT_Rd, HANDLE g_hOutputFile);

#endif // INC_1_UTILS_H