
//---------------------------------------------------------------------------
#ifndef UnitMathH
#define UnitMathH
//---------------------------------------------------------------------------
#ifdef __cplusplus

#include <windows.h>
#include <cmath>

extern "C"
{
#endif

	__declspec(dllexport) float __cdecl Pi_V1(int K);
	__declspec(dllexport) float __cdecl Pi_V2(int K);
	__declspec(dllexport) float __cdecl E_V1(int x);
	__declspec(dllexport) float __cdecl E_V2(int x);

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
#endif