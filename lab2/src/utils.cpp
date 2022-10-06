#include "utils.h"

void WriteToPipe(HANDLE g_hChildStd_IN_Wr, HANDLE g_hChildStd_IN_Wr_2, std::ifstream &inFile)
// Чтение из ifstream и запись его содержимого в каналы для дочерних STDIN.
{
	DWORD dwWritten;
	BOOL bSuccess = FALSE;

	std::string s;
	while (std::getline(inFile, s))
	{
		//  фильтрация строк по варианту
		s += "\n";
		if ((s.size() - 1) % 2 == 1)
		{
			bSuccess = WriteFile(g_hChildStd_IN_Wr, s.c_str(),
										s.size(), &dwWritten, NULL);
			if (!bSuccess)
				break;
		}
		else
		{
			bSuccess = WriteFile(g_hChildStd_IN_Wr_2, s.c_str(),
										s.size(), &dwWritten, NULL);
			if (!bSuccess)
				break;
		}
	}

	// Закрываем дескрипторы каналов, чтобы дочерние процессы прекратили чтение.
	if (!CloseHandle(g_hChildStd_IN_Wr_2))
		std::cout << "error closed ChildStd_IN_Wr_2";
	if (!CloseHandle(g_hChildStd_IN_Wr))
		std::cout << "error ChildStd_IN_Wr";
}

void ReadFromPipe(HANDLE g_hChildStd_OUT_Rd, HANDLE g_hOutputFile)
// Чтение вывода из канала дочернего процесса_1 для STDOUT
// И записываем в файл_1.
{
	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFSIZE];
	BOOL bSuccess = FALSE;

	for (;;)
	{
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf,
								  BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0)
			break;

		bSuccess = WriteFile(g_hOutputFile, chBuf,
									dwRead, &dwWritten, NULL);
		if (!bSuccess)
			break;
	}
	if (!CloseHandle(g_hChildStd_OUT_Rd))
		std::cout << "error closed ChildStd_OUT_Rd";
	if (!CloseHandle(g_hOutputFile))
		std::cout << "error closed OutputFile";
}
