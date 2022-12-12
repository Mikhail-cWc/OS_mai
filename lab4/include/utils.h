#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>
#include <algorithm>

void WriteToMapFile(std::istream &inFile, LPVOID lpMapAdress);

#endif // INC_1_UTILS_H