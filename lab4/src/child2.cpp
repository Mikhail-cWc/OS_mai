#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>

int main(void)
{
	LPCSTR FileMapName = "mainfile";

	HANDLE hMapFile;
	LPVOID lpMapAddress;

	std::string name_OutputFile;
	HANDLE g_hOutputFile1;

	std::string result;
	DWORD dwWritten;

	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, FileMapName);
	if (hMapFile == NULL)
		std::cerr << "ПРОЦЕСС 2. НЕВОЗМОЖНО ОТКРЫТЬ ОБЪЕКТ ПРОЕКЦИИ ФАЙЛА";

	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpMapAddress == NULL)
		std::cerr << "ПРОЦЕСС 2. ПРЕДСТАВЛЕНИЕ ПРОЕЦИРОВАННОГО ФАЙЛА НЕ ВОЗМОЖНО";

	TCHAR *datafromfile = (TCHAR *)lpMapAddress;
	std::string s(datafromfile);

	int countstr = 0;
	int i = 0;
	while (i < s.size())
	{
		if (s[i] != '\n')
			name_OutputFile += s[i];
		else
		{
			countstr++;
			if (countstr == 2)
				break;
			else
				name_OutputFile = "";
		}
		i++;
	}
	g_hOutputFile1 = CreateFile(name_OutputFile.c_str(),
										 FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS,
										 FILE_ATTRIBUTE_NORMAL, NULL);

	if (g_hOutputFile1 == INVALID_HANDLE_VALUE)
		std::cerr << "ПРОЦЕСС 2. ОШИБКА В СОЗДАНИИ ФАЙЛА ДЛЯ ВЫВОДА\n";

	for (int j = i; j < s.size(); j++)
	{
		if (s[j] != '\n')
			result += s[j];
		else
		{
			if (result.size() % 2 == 1)
			{
				reverse(result.begin(), result.end());
				result += '\n';
				if (!WriteFile(g_hOutputFile1, result.c_str(),
									result.size(), &dwWritten, NULL))
					std::cerr << "ПРОЦЕСС 2. ОШИБКА ЗАПИСИ\n";
			}
			result = "";
		}
	}
	UnmapViewOfFile(lpMapAddress);
	CloseHandle(hMapFile);
	return 0;
}