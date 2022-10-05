#include "utils.h"
int main()
{
	std::string inFileName = "C:\\test.txt";
	std::string outFileName1 = "test1.txt";
	std::string outFileName2 = "test2.txt";

	ParentRoutine(inFileName, outFileName1, outFileName2);
	return 0;
}