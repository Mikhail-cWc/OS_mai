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
		std::cerr << "PROCESS 1. UNABLE TO OPEN FILE PROJECTION OBJECT";

	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpMapAddress == NULL)
		std::cerr << "PROCESS 1. PROJECTED FILE PRESENTATION IS NOT POSSIBLE";

	TCHAR *datafromfile = (TCHAR *)lpMapAddress;
	std::string s(datafromfile);

	int countstr = 0;
	int i = 0;
	while (s[i] != '\n')
	{
		name_OutputFile += s[i];
		i++;
	}
	g_hOutputFile1 = CreateFile(name_OutputFile.c_str(),
										 FILE_SHARE_WRITE, 0, NULL, CREATE_ALWAYS,
										 FILE_ATTRIBUTE_NORMAL, NULL);

	if (g_hOutputFile1 == INVALID_HANDLE_VALUE)
		std::cerr << "PROCESS 1. ERROR IN CREATING THE OUTPUT FILE\n";

	for (int j = i + 1; j < s.size(); j++)
	{
		if (s[j] != '\n')
			result += s[j];
		else
		{
			countstr += 1;
			if ((result.size() % 2 == 0) && (countstr != 1))
			{
				reverse(result.begin(), result.end());
				result += '\n';
				if (!WriteFile(g_hOutputFile1, result.c_str(),
									result.size(), &dwWritten, NULL))
					std::cerr << "PROCESS 1. WRITE ERROR\n";
			}
			result = "";
		}
	}
	UnmapViewOfFile(lpMapAddress);
	CloseHandle(hMapFile);
	return 0;
}