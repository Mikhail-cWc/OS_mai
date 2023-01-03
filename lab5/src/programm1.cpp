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

int programm1(std::istream &inFile, const char *fileWithOutput1)
{
	std::ofstream outFile(fileWithOutput1);

	std::string command;

	outFile << std::fixed;

	outFile.precision(15);

	while (std::getline(inFile, command))
	{

		if (command[0] == '1')
			outFile << Pi_V1(argument(command)) * 4 << std::endl;

		if (command[0] == '2')
			outFile << E_V1(argument(command)) << std::endl;

		if (command[0] != '1' && command[0] != '2')
			outFile << "invalid_command\n";
	}
	outFile.close();
	return 0;
}
