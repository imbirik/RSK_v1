#pragma once

#include <vector>
#include "random.h"

using namespace std;

template<typename T>
void permutate(vector<T> &, const vector<int> &);        //Apply permutation to vector
template<typename T>
int count_identity_points(vector<T> &);                  //Count the number of identity points
template<typename T>
inline void rand_permute_self_inverse(
	T*, long, long *,
	long double *, bool);                                //Return involution of length n
void init_involution_branch_prob(long double*, long);    //Count branch probabilities for generating random involution 



//implementation


template<typename T>
void permutate(vector<T>& value, const vector<int>& permutation)
{
	auto new_value = value;
	for (int i = 0; i < (int)value.size(); ++i)
	{
		new_value[permutation[i]] = value[i];
	}
	for (int i = 0; i < (int)value.size(); ++i)
	{
		value[i] = new_value[i];
	}
	return;
}
template<typename T>
int count_identity_points(vector<T>& vec)
{
	vector<pair<T, int>> new_vec(vec.size());
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		new_vec[i] = { vec[i], i };
	}
	sort(new_vec.begin(), new_vec.end());
	int identity_points = 0;
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		identity_points += new_vec[i].second == i;
	}
	return identity_points;
}
template<typename T>                                    //not finished yet, destructor needs some treatment
void rand_permute_self_inverse(T *f, long n,
	long *tr = 0,
	long double *tb = 0, bool bi = false)
	// Permute the elements of f by a random involution.
	// Set bi:=true to signal that the branch probabilities in tb[]
	// have been precomputed (via init_involution_branch_ratios()).
{
	long *r = tr;
	if (tr == 0) r = new long[n];
	for (long k = 0; k < n; ++k) r[k] = k;
	long nr = n;                                         // number of elements available
														 // available positions are r[0], ..., r[nr-1]

	long double *b = tb;
	if (tb == 0) { b = new long double[n]; bi = false; }
	if (!bi) init_involution_branch_prob(b, n);

	while (nr >= 2)
	{
		const long x1 = nr - 1;                           // choose last element
		const long r1 = r[x1];                            // available position
														  // remove from set:
		--nr;                                             // no swap needed if x1==last

		const long double rat = b[nr];                    // probability to choose fixed point

		const long double t = rand01();                   // 0 <= t < 1
		if (t > rat)                                      // 2-cycle
		{
			const long x2 = randN(nr);
			const long r2 = r[x2];                        // random available position != r1
			--nr; swap(r[x2], r[nr]);                     // remove from set
			swap(f[r1], f[r2]);                           // create a 2-cycle
		}
		// else fixed point, nothing to do
	}

	//if (tr == 0) delete[] r;
	//if (tb == 0) delete[] b;
}