#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>

int main(void)
{
	DWORD dwWritten;
	HANDLE hStdin, hStdout;
	BOOL bSuccess;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (
		 (hStdout == INVALID_HANDLE_VALUE) ||
		 (hStdin == INVALID_HANDLE_VALUE))
		ExitProcess(1);

	std::string s;
	while (std::getline(std::cin, s))
	{

		std::reverse(s.begin(), s.end());
		s += "\n";
		bSuccess = WriteFile(hStdout, s.c_str(), s.size(), &dwWritten, NULL);
		if (!bSuccess)
			break;
	}
	return 0;
}