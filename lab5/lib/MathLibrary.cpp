// The myPuts function writes a null-terminated string to
// the standard output device.

// The export mechanism used here is the __declspec(export)
// method supported by Microsoft Visual Studio, but any
// other export method supported by your development
// environment may be substituted.

#include "MathUnit.h"

float __cdecl Pi_V1(int K)
{
    float res = 0;
    for (int i = 0; i <= K - 1; i++)
    {
        res += pow(-1, i) / (2 * i + 1);
    }
    return res;
}

float __cdecl Pi_V2(int K)
{
    float res = 1;
    for (int i = 1; i <= K - 1; i++)
    {
        res *= (4. * i * i) / ((2. * i - 1.) * (2. * i + 1.));
    }
    res *= ((2. * K) / (2. * K - 1.)) * (((2. * K) / (8. * K + 4.)) + 1.) + 3. / 4.;
    return res;
}

float __cdecl E_V1(int x)
{
    float res = 1;
    float fact = 1;
    for (int i = 1; i <= x; i++)
    {
        res += fact * (1.0 / i);
        fact = fact * (1.0 / i);
    }
    return res;
}

float __cdecl E_V2(int x)
{
    float res = 1;
    float fact = 1;
    for (int i = 1; i <= x; i++)
    {
        res += fact * (1.0 / i);
        fact = fact * (1.0 / i);
    }
    return res;
}
