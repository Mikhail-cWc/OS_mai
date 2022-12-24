#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

typedef float(__cdecl *MYPROC)(int);

int argument(std::string s)
{
	std::string res = "";
	for (int i = 2; i < s.size(); i++)
		res += s[i];
	return std::stoi(res);
}

int main(void)
{
	HINSTANCE hinstLib;
	MYPROC Pi, E;
	bool fFreeResult, fRunTimeLinkSuccess = FALSE, flag = FALSE;
	std::string command;

	std::cout << std::fixed;

	std::cout.precision(15);

	hinstLib = LoadLibrary(TEXT("..\\build\\lab5\\libexample.dll"));

	// If the handle is valid, try to get the function address.

	if (hinstLib != NULL)
	{
		Pi = (MYPROC)GetProcAddress(hinstLib, "Pi_V1");
		E = (MYPROC)GetProcAddress(hinstLib, "E_V1");
		while (std::getline(std::cin, command))
		{
			if (command[0] == '0')
			{
				std::cout << "Переключение реализации математических функций.\n";
				if (!flag)
				{
					Pi = (MYPROC)GetProcAddress(hinstLib, "Pi_V2");
					E = (MYPROC)GetProcAddress(hinstLib, "E_V2");
					flag = TRUE;
				}
				else
				{
					Pi = (MYPROC)GetProcAddress(hinstLib, "Pi_V1");
					E = (MYPROC)GetProcAddress(hinstLib, "E_V1");
					flag = FALSE;
				}
			}

			if (command[0] == '1')
			{
				if (NULL != Pi && flag)
					std::cout << Pi(argument(command)) << std::endl;
				else if (NULL != Pi)
					std::cout << Pi(argument(command)) * 4 << std::endl;
				else
					std::cerr << "Error load proc Pi";
			}
			if (command[0] == '2')
			{
				if (NULL != E)
					std::cout << E(argument(command)) << std::endl;
				else
					std::cerr << "Error load proc E";
			}

			if (command[0] != '0' && command[0] != '1' && command[0] != '2')
				std::cout << "invalid command";
				}
		// Free the DLL module.
		fFreeResult = FreeLibrary(hinstLib);
	}
	else
		std::cerr << "Error load library DLL\n";

	return 0;
}