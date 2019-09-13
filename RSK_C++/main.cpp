#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include "young.h"
#include <set>
#include <random>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

const size_t MAXN = (size_t)1e4;                 //size of YT
const double EPS = 1e-8;
long long factorial[20];
//const unsigned int N = 5;
//long double branch_prob[MAXN];

int main() {
	freopen("out.txt", "w", stdout);
	//freopen("err.txt", "w", stderr);
	cout.precision(6);

	size_t N = MAXN;
	double *r = new double[N];
	rand_arr(r, N);
	PQ_tableaux<double> PQ;
	PQ.push(r, N);

	double *points = new double[1];
	rand_arr(points, 1);
	trace = PQ.push(rand_arr[0]);
	print(trace);
	/*
	for (size_t i = 0; i < 10; ++i)
	{
		points[i] = ((double)i + 1) / 10;
	}
	const size_t M = (size_t)1e5;
	pair<double, double> coord[10][M / 100];
	PQ.push(points, 10);

	for (size_t i = 0; i < M; ++i)
	{
		PQ.push(rand01());
		if (i % 100 == 0)
		{
			for (size_t j = 0; j < 10; ++j)
			{
				coord[j][i / 100] = PQ.find(points[j]);
			}
		}
	}

	for (size_t i = 0; i < M / 100; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			cout << coord[j][i].first << ' ' << coord[j][i].second << ' ';
		}
		cout << "\n";
	}*/

	//system("pause");
	/*
	double add = 1 / (double)MAXN;
	double r = 0;
	for (size_t i = 0; i < MAXN; ++i)
	{
		ra[i] = r;
		r += add;
	}

	rand_permute_self_inverse(ra, MAXN);
	*/
	/*
	const long MAN = (long)2e2;
	long *func = new long[MAN];
	long *height = new long[MAN];
	long *length = new long[MAN];
	for (size_t MAXN = 1; MAXN < MAN; ++MAXN)
	{
		cerr << MAXN << "\n";
		double *ra = 0;
		ra = new double[MAXN];
		rand_arr(ra, MAXN);
		PQ_tableaux<double> PQ;
		PQ.push(ra, MAXN);
		height[MAXN] = PQ.height();
		length[MAXN] = PQ.length();

		double *max_ra = new double[MAXN];
		for (size_t cnt = 0; cnt * cnt < 16 * MAXN; ++cnt)
		{
			for (size_t i = 0; i < MAXN; ++i)
			{
				double tmp = 0;
				for (size_t j = 0; j < i; ++j)
				{
					tmp = max(tmp, (ra[j] < ra[i]) ? ra[j] : 0);
				}
				max_ra[i] = tmp;
			}
			PQ_tableaux<double> PQ_max;
			PQ_max.push(max_ra, MAXN);
			if (PQ_max.height() == 1)
			{
				func[MAXN] = cnt;
				break;
			}
			for (size_t i = 0; i < MAXN; ++i)
			{
				ra[i] = max_ra[i];
			}
		}
	}

	for (size_t i = 0; i < MAN; ++i)
	{
		cout << i << ' ' << func[i] << ' ' << length[i] << ' ' << height[i] << "\n";
	}
	*/
	/*
	PQ.showP();
	cout << "\n\n";
	PQ.truncate(max_ra[9], ra[9]);
	PQ.showP();
	cout << "\n\n";
	PQ.truncate(max_ra[89], ra[89]);
	PQ.showP();
	cout << "\n\n";
	*/



	/*
	int n = 6000;
	for (int my_try = 0; my_try < 100; my_try++) {
		vector <double> vec = rand_vec(n);
		PQ_tableaux PQ;
		PQ.push(vec);
		for (int i = 0; i < 1; i++)
			cout << vec[i] << " " << sqrt(PQ.find(vec[i])) / sqrt(n) << " " << vec[i] / ((PQ.find(vec[i]) + 1) / sqrt(n)) << endl;
	}
	*/


	/*
	factorial[0] = 1;                                                //Trying to count some statistics on small sizes of YT
	for (int i = 1; i < 20; ++i)                                     //Firstly, some precounting
	{
		factorial[i] = factorial[i - 1] * i;
	}

	for (int N = 1; N < 5; ++N)
	{
		//vector<double> vec = { 5, 2, 4, 3, 1, 7, 6 };
		vector<double> vec = rand_vec(N);
		vector<double> vec_copy = vec;
		cout << "random vector: " << vec << "\n";
		vector<int> permutation(N);
		map<vector<int>, vector<double>> identity_points;                   //Map contains info about each type of YT
		for (int i = 0; i < N; ++i)                                      //For each type: an array with numbers of
		{
			permutation[i] = i;                                          //the permutation number which contains
		}                                                                //this number of identity points
		for (int i = 0; i < factorial[N]; ++i)
		{
			permutate(vec, permutation);
			PQ_tableaux PQ;
			PQ.push(vec);
			if (identity_points.find(PQ.type()) == identity_points.end())
			{
				identity_points[PQ.type()] = vector<double>(N + 1);
			}
			identity_points[PQ.type()][count_identity_points(vec)]++;
			next_permutation(permutation.begin(), permutation.end());
			vec = vec_copy;
		}

		vector<double> measure(N + 1, 0);
		for (auto i : identity_points)
		{
			cout << i.first << "\n" << i.second << "\n";
			measure = measure + i.second;
		}
		int total = 0;
		cout << "Plancherel measure: ";
		for (auto i : identity_points)
		{
			cout << sum(i.second) << " ";
			total += sum(i.second);
		}
		cout << "\n" << "total: " << total << "\n";
		cout << "id_points statistics for all permutation: " << measure << "\n" << "\n";
	}
	*/
	//system("pause");
	return 0;
	/*
	PQ_tableaux PQ;
	PQ.push({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1 });
	cout << PQ;
	vector <double> per;
	for (int i = 0; i < PQ.size(); i++) {
		per.push_back(PQ.erase());
	}
	reverse(per.begin(),per.end());
	for (int i = 0; i < per.size(); i++)
		cout << per[i] <<" ";
	return 0;
	*/
}