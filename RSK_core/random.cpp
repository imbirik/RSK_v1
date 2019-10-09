#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif
#include <random>
#include <ctime>
#include "random.h"

using namespace std;

long randN(long N)
{
	long tmp = rand() ^ (rand() << 16);
	return tmp % N;
}
double rand01(double acc)
{
	static bool f = false;
	if (!f)
	{
		double tme = (double)time(NULL);
		srand(tme);
		f = true;
	}
	double rand_num = ((rand() ^ (rand() << 16)) % (int)acc) / acc;
	return rand_num;
}
void rand_arr(double* ra, size_t n)
{
	for (size_t i = 0; i < n; i++)
		ra[i] = rand01();
	return;
}
