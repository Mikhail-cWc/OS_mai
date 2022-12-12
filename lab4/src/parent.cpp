#include "utils.h"
#include "parent.h"
int ParentRoutine(std::istream &inFile)
{

	HANDLE hMapFile; // handle for the file's memory-mapped region
	HANDLE hFile;
	LPVOID lpMapAddress;

	std::string child1 = "..\\lab4\\child3.exe";
	std::string child2 = "..\\lab4\\child4.exe";

	TCHAR *lpcTheFile = TEXT("fmtest.txt");

	LPCSTR FileMapName = "mainfile";
	hFile = CreateFile(lpcTheFile,
							 GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
							 FILE_ATTRIBUTE_NORMAL, NULL);

	hMapFile = CreateFileMapping(hFile,				// current file handle
										  NULL,				// default security
										  PAGE_READWRITE, // read/write permission
										  0,					// size of mapping object, high
										  1024, FileMapName);

	lpMapAddress = MapViewOfFile(hMapFile,				  // handle to
										  FILE_MAP_ALL_ACCESS, // read/write
										  0, 0, 0);

	//----------------------------

	WriteToMapFile(inFile, lpMapAddress);

	HANDLE ProcInfo[2];
	ProcInfo[0] = CreateChildProcess(child1);
	ProcInfo[1] = CreateChildProcess(child2);

	WaitForMultipleObjects(2, ProcInfo, TRUE, INFINITE);

	for (int i = 0; i < 2; i++)
		CloseHandle(ProcInfo[i]);

	UnmapViewOfFile(lpMapAddress);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	remove("fmtest.txt");

	return 0;
}

HANDLE CreateChildProcess(std::string child)
{
	// string -> TCHAR
	TCHAR *szCmdline = 0;
	szCmdline = new TCHAR[child.size() + 1];
	copy(child.begin(), child.end(), szCmdline);
	szCmdline[child.size()] = 0;

	PROCESS_INFORMATION piProcInfo = {0};
	STARTUPINFO siStartInfo = {0};
	BOOL bSuccess = FALSE;

	bSuccess = CreateProcess(NULL,
									 szCmdline,		// command line
									 NULL,			// process security attributes
									 NULL,			// primary thread security attributes
									 TRUE,			// handles are inherited
									 0,				// creation flags
									 NULL,			// use parent's environment
									 NULL,			// use parent's current directory
									 &siStartInfo, // STARTUPINFO pointer
									 &piProcInfo); // receives PROCESS_INFORMATION

	if (!bSuccess)
		std::cerr << "Error created process\n";

	else
	{
		CloseHandle(piProcInfo.hThread);
	}
	return piProcInfo.hProcess;
}
