#include "utils.h"
#include "MathUnit.h"

__declspec(dllimport) float __cdecl Pi_V1(int);
__declspec(dllimport) float __cdecl E_V1(int); // a function from a DLL

int argument(std::string s)
{
	std::string res = "";
	for (int i = 2; i < s.size(); i++)
		res += s[i];
	return std::stoi(res);
}

int programm1(std::istream &inFile)
{
	std::string command;

	std::cout << std::fixed;

	std::cout.precision(15);

	while (std::getline(inFile, command))
	{

		if (command[0] == '1')
			std::cout << Pi_V1(argument(command)) << std::endl;

		if (command[0] == '2')
			std::cout << E_V1(argument(command)) << std::endl;

		if (command[0] != '1' && command[0] != '2')
			std::cout << "invalid command\n";
	}
	return 0;
}
