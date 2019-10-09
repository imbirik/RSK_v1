#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include "young.h"
#include "random.h"
#include "py_out.h"
#include "my_time.h"
#include <set>
#include <random>
#include <algorithm>
#include <map>
#include <ctime>
#include <fstream>

#define Q(X, Y) vector<pair<X, Y>>

using namespace std;


const size_t MAXN = (size_t)1000000;
const double EPS = 1e-8;                          //size of y-axis neighborhood
const double АСС = 1e-12;                         //computation accuracy
const size_t NUM = 200;                            //number of experiments
const size_t STEP = 50000;
const vector<size_t> N = {300};   //size of initial YT

size_t ex_f(size_t n)
{
	return n * n;
}



int main() {
	ofstream trace_out("traces.txt");
	ofstream elem_trace_out("elem_traces.txt");
	//freopen("tabluax.txt", "w", stdout);
	//freopen("err.txt", "w", stderr);


	size_t cnt = 0;
	vector < vector<Q(size_t, size_t)>> tracks(N.size(), vector<Q(size_t, size_t)>(NUM));
	init_time();

	int k = 0;
	for (auto N : N)
	{
		for (size_t i = 0; i < NUM; i++)
		{
			cerr << N << ' ' << i << "\n";
			double* r = new double[N];
			rand_arr(r, N);
			PQ_tableaux <double>* PQ = new PQ_tableaux<double>;
			PQ->push(r, N);
			coord track_pair = mp(PQ->length(), 0);
			PQ->push(1);
			tracks[k][i].push_back(mp(track_pair.first, 1));
			coord new_track_pair;
			for (size_t j = 0; j < ex_f(N); ++j)
			{
				new_track_pair = track_pair;
				PQ->push(rand01(), new_track_pair);   cnt++;
				if (cnt % STEP == 0)
					cerr << cnt << " " << full_exec_time() << "\n";
				if (new_track_pair == track_pair)
					tracks[k][i].back().second++;
				else
					tracks[k][i].push_back(mp(new_track_pair.first, 1));
				track_pair = new_track_pair;
			}
			delete[] r;
			delete PQ;
		}
		k++;
	}

	trace_out << "[[";
	trace_out << NUM << ", " << N.size() << "],";
	out_for_py(N, trace_out);
	trace_out << ",";
	out_for_py(tracks, trace_out);
	trace_out << "]";



	return 0;
}