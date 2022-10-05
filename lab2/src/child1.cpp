#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#define BUFSIZE 4096
int main(void)
{
	DWORD dwRead, dwWritten;
	HANDLE hStdin, hStdout;
	BOOL bSuccess;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (
		 (hStdout == INVALID_HANDLE_VALUE) ||
		 (hStdin == INVALID_HANDLE_VALUE))
		ExitProcess(1);

	for (;;)
	{
		CHAR *chBuf = new CHAR[BUFSIZE];

		// Чтение со стандартного ввода и остановка при ошибке или отсутствии данных.
		bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0)
			break;

		std::reverse(chBuf, chBuf + dwRead-1);
		//  Запись в стандартный вывод и остановка при ошибке.
		bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL);
		if (!bSuccess)
			break;
	}
	return 0;
}