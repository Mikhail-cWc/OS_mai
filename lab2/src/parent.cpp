#include "parent.h"
#include "utils.h"

int ParentRoutine(std::string inFileName, std::string outFileName1, std::string outFileName2)
{
	// флаг bInheritHandle, чтобы дескрипторы каналов наследовались.
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Канал для стандартного выхода доч. процесса
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
	{
		std::cout << "Error Pipe1\n";
		return -1;
	}

	// Канал для стандартного входа доч. процесса
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
	{
		std::cout << "Error Pipe1\n";
		return -1;
	}
	// g_hChildStd_OUT_rd не должен наследоваться

	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		return -2;

	// g_hChildStd_IN_Wr не должен наследоваться
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
		return -2;

	// Аналогично для доч. процесса 2.

	if (!CreatePipe(&g_hChildStd_OUT_Rd_2, &g_hChildStd_OUT_Wr_2, &saAttr, 0))
	{
		std::cout << "Error Pipe2\n";
		return -1;
	}

	if (!CreatePipe(&g_hChildStd_IN_Rd_2, &g_hChildStd_IN_Wr_2, &saAttr, 0))
	{
		std::cout << "Error Pipe2\n";
		return -1;
	}

	if (!SetHandleInformation(g_hChildStd_OUT_Rd_2, HANDLE_FLAG_INHERIT, 0))
		return -2;

	if (!SetHandleInformation(g_hChildStd_IN_Wr_2, HANDLE_FLAG_INHERIT, 0))
		return -2;

	//----------------------------

	CreateChildProcess(g_hChildStd_OUT_Wr, g_hChildStd_IN_Rd, child1);
	CreateChildProcess(g_hChildStd_OUT_Wr_2, g_hChildStd_IN_Rd_2, child2);

	//  Доступ к записи,,,всегда создавать(перезаписывать) файл, не уст. др. атрибуты,
	g_hOutputFile1 = CreateFile((LPCSTR)outFileName1.c_str(), FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	g_hOutputFile2 = CreateFile((LPCSTR)outFileName2.c_str(), FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteToPipe(g_hChildStd_IN_Wr, g_hChildStd_IN_Wr_2, inFileName);
	ReadFromPipe1(g_hChildStd_OUT_Rd, g_hOutputFile1);
	ReadFromPipe2(g_hChildStd_OUT_Rd_2, g_hOutputFile2);

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
