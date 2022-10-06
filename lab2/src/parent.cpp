#include "utils.h"
#include "parent.h"
int ParentRoutine(std::string inFileName) //, std::string outFileName1, std::string outFileName2)
{
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

	std::string child1 = "..\\lab2\\child1.exe";
	std::string child2 = "..\\lab2\\child2.exe";

	HANDLE g_hOutputFile1 = NULL;
	HANDLE g_hOutputFile2 = NULL;
	// флаг bInheritHandle, чтобы дескрипторы каналов наследовались.
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Канал для стандартного выхода доч. процесса 1
	PipeStdOut(g_hChildStd_OUT_Rd, g_hChildStd_OUT_Wr, saAttr);
	// Канал для стандартного входа доч. процесса 1
	PipeStdIn(g_hChildStd_IN_Rd, g_hChildStd_IN_Wr, saAttr);
	// Канал для стандартного выхода доч. процесса 2
	PipeStdOut(g_hChildStd_OUT_Rd_2, g_hChildStd_OUT_Wr_2, saAttr);
	// Канал для стандартного входа доч. процесса 1
	PipeStdIn(g_hChildStd_IN_Rd_2, g_hChildStd_IN_Wr_2, saAttr);

	//----------------------------

	CreateChildProcess(g_hChildStd_OUT_Wr, g_hChildStd_IN_Rd, child1);
	CreateChildProcess(g_hChildStd_OUT_Wr_2, g_hChildStd_IN_Rd_2, child2);

	auto inFile = std::ifstream(inFileName.c_str());

	std::string outFileName1, outFileName2;
	std::getline(inFile, outFileName1);
	std::getline(inFile, outFileName2);
	//  Доступ к записи,,,всегда создавать(перезаписывать) файл, не уст. др. атрибуты,
	g_hOutputFile1 = CreateFile((LPCSTR)outFileName1.c_str(), FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	g_hOutputFile2 = CreateFile((LPCSTR)outFileName2.c_str(), FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteToPipe(g_hChildStd_IN_Wr, g_hChildStd_IN_Wr_2, inFile);
	ReadFromPipe(g_hChildStd_OUT_Rd, g_hOutputFile1);
	ReadFromPipe(g_hChildStd_OUT_Rd_2, g_hOutputFile2);

	return 0;
}

void CreateChildProcess(HANDLE ChildStd_OUT_Wr, HANDLE ChildStd_IN_Rd, std::string child)
{
	// string -> TCHAR
	TCHAR *szCmdline = 0;
	szCmdline = new TCHAR[child.size() + 1];
	copy(child.begin(), child.end(), szCmdline);
	szCmdline[child.size()] = 0;

	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// STARTUPINFO structure.
	// Определяем дескрипторы STDIN и STDOUT для перенаправления.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = ChildStd_OUT_Wr;
	siStartInfo.hStdOutput = ChildStd_OUT_Wr;
	siStartInfo.hStdInput = ChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

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
		std::cout << "Error created process\n";

	else
	{
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		// Зыкрываем дескрипторы дочернего процесса и его основного потока

		// Закрываем дескрипторы каналов stdin и stdout, которые больше не нужны дочернему процессу.
		CloseHandle(ChildStd_OUT_Wr);
		CloseHandle(ChildStd_IN_Rd);
	}
}

int PipeStdOut(HANDLE &g_hChildStd_OUT_Rd, HANDLE &g_hChildStd_OUT_Wr, SECURITY_ATTRIBUTES saAttr)
{
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
	{
		std::cout << "Error Pipes\n";
		return -1;
	}
	// g_hChildStd_OUT_rd не должен наследоваться
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		return -2;
}

int PipeStdIn(HANDLE &g_hChildStd_IN_Rd, HANDLE &g_hChildStd_IN_Wr, SECURITY_ATTRIBUTES saAttr)
{
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
	{
		std::cout << "Error Pipes\n";
		return -1;
	}
	// g_hChildStd_IN_Wr не должен наследоваться
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
		return -2;
}