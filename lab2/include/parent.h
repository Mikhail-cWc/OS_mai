#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>

int ParentRoutine(std::istream &inFile);
void CreateChildProcess(HANDLE ChildStd_OUT_Wr, HANDLE ChildStd_IN_Rd, std::string child);
int PipeStdOut(HANDLE &g_hChildStd_OUT_Rd, HANDLE &g_hChildStd_OUT_Wr, SECURITY_ATTRIBUTES saAttr);
int PipeStdIn(HANDLE &g_hChildStd_IN_Rd, HANDLE &g_hChildStd_IN_Wr, SECURITY_ATTRIBUTES saAttr);

#endif // OS_LABS_PARENT_H