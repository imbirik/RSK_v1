#pragma once

#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

void out_for_py(const size_t, ofstream&);

template <typename T1, typename T2> void out_for_py(const pair<T1, T2>&, ofstream&);
template <typename T>               void out_for_py(const vector<T>&, ofstream&);
template <typename T>               void out_for_py(const vector<vector<T>>&, ofstream&);
template <typename T>               void out_for_py(const vector<vector<vector<T>>>&, ofstream&);

void out_for_py(const size_t q, ofstream& out)
{
	out << q;
	return;
}

template <typename T1, typename T2> void out_for_py(const pair<T1, T2>& q, ofstream& out)
{
	out << '[' << q.first << ", " << q.second << ']';
	return;

}
template <typename T>               void out_for_py(const vector<T>& q, ofstream& out)
{
	out << "[";
	if (!q.empty())
	{
		for (size_t j = 0; j < q.size() - 1; j++) {
			out_for_py(q[j], out);
			out << ", ";
		}
		out_for_py(q.back(), out);
		out << "]";
	}
	return;

}
template <typename T>               void out_for_py(const vector<vector<T>>& q, ofstream& out)
{
	out << "[";
	if (!q.empty())
	{
		for (size_t j = 0; j < q.size() - 1; j++) {
			out_for_py(q[j], out);
			out << ", ";
		}
		out_for_py(q.back(), out);
		out << "]";
	}
	return;

}
template <typename T>               void out_for_py(const vector<vector<vector<T>>>& q, ofstream& out)
{
	out << "[";
	if (!q.empty())
	{
		for (size_t j = 0; j < q.size() - 1; j++) {
			out_for_py(q[j], out);
			out << ", ";
		}
		out_for_py(q.back(), out);
		out << "]";
	}
	return;

}