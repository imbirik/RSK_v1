#include <vector>
#include "permutations.h"
#include <algorithm>

using namespace std;

void init_involution_branch_prob(long double * b, long n)  //count branch prob. for involutions
{
	b[1] = 1;
	for (int i = 1; i < n; ++i)
	{
		b[i + 1] = 1 / (1 + i * b[i]);
	}
	return;
}