#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>

int ParentRoutine(std::istream &inFile);
HANDLE CreateChildProcess(char *child);

#endif // OS_LABS_PARENT_H