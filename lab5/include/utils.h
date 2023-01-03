#ifndef OS_LABS_UTILS_H
#define OS_LABS_UTILS_H

#include <windows.h>
#include <iostream>
#include <fstream>

typedef float(__cdecl *MYPROC)(int);

int programm1(std::istream &inFile, const char *fileWithOutput1);
int argument(std::string s);
int programm2(std::istream &inFile,  const char *fileWithOutput2);

#endif // OS_LABS_PROG2_H