#include "utils.h"
void WriteToMapFile(std::istream &inFile, LPVOID lpMapAdress)
{
	std::string s;
	std::string resstr = "";
	while (std::getline(inFile, s))
		resstr += (s + '\n');

	CopyMemory(lpMapAdress, resstr.c_str(), resstr.size());
}
