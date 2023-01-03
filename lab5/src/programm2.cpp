#include "utils.h"

int programm2(std::istream &inFile, const char *fileWithOutput2)
{
	std::ofstream outFile(fileWithOutput2);

	HINSTANCE hinstLib;
	MYPROC Pi, E;
	bool flag = FALSE;
	std::string command;

	outFile << std::fixed;

	outFile.precision(15);

	hinstLib = LoadLibrary(TEXT("libmath.dll"));

	// If the handle is valid, try to get the function address.

	if (hinstLib != NULL)
	{
		Pi = (MYPROC)GetProcAddress(hinstLib, "Pi_V1");
		E = (MYPROC)GetProcAddress(hinstLib, "E_V1");
		while (std::getline(inFile, command))
		{
			if (command[0] == '0')
			{
				outFile << "Swithing_the_implementation_of_mathematical_function\n";
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
					outFile << Pi(argument(command)) << std::endl;
				else if (NULL != Pi)
					outFile << Pi(argument(command)) * 4 << std::endl;
				else
					std::cerr << "Error load proc Pi\n";
			}
			if (command[0] == '2')
			{
				if (NULL != E)
					outFile << E(argument(command)) << std::endl;
				else
					std::cerr << "Error load proc E\n";
			}

			if (command[0] != '0' && command[0] != '1' && command[0] != '2')
				outFile << "invalid_command\n";
		}
		// Free the DLL module.
		if (!FreeLibrary(hinstLib))
			std::cerr << "Error FleeLibrary\n";
	}
	else
		std::cerr << "Error load library DLL\n";

	return 0;
}
