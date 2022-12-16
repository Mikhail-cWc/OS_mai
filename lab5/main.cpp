#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <strsafe.h>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
	int k;
	cin >> k;
	float res = 0;
	for (int i = 0; i <= k-1; i++)
	{
		res += pow(-1,i)/(2*i+1);
	}
	cout << res*4 << endl;
	res = 1;
	for (int i = 1; i <= k-1; i++)
	{
		res*=pow(2*i,2)/((2*i-1)*(2*i+1));
	}
	cout << res*2 << endl;


	float x;
	cin >> x;
	x = INFINITY;
	cout << pow(1+1/x,x)<<endl;
	return 0;
}