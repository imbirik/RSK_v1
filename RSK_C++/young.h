#pragma once
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <utility>
#include "permutations.h"
#include "random.h"
#define space8 "        "
#define INF (int)1e8
#define mp make_pair

using namespace std;

template<class T>
class Row {                                             //Row of Young tableau consisting of real numbers
public:
	Row() :
		_left_bound(0),
		_right_bound(INF)
	{}
	Row(T);
	Row(T *, size_t n);
	size_t size();                                      //Return size of row
	T reverse_Shensted_insert(T);                       //Reverse bumping
	size_t lower_bound(T x);
	size_t upper_bound(T x);
	friend ostream& operator<<(                         //Printing the row
		ostream& out,
		Row<T>& obj
		)
	{
		auto ind_low = obj._row.begin() + obj.upper_bound(obj._left_bound);
		auto ind_upper = obj._row.begin() + obj.upper_bound(obj._right_bound);
		for (auto it = obj._row.begin(); it != ind_low; ++it)
		{
			//out << space8 << "   \t";
			out << " ";
		}
		out << setprecision(6) << fixed;
		out << "[";
		for (auto it = ind_low; it != ind_upper; ++it)
		{
			//out << *it << "   \t";
			auto it_ = it;
			if (++it_ == ind_upper)
			{
				out << *it;
			}
			else
			{
				out << *it << ", ";
			}
		}
		out << "]";
		for (auto it = ind_upper; it != obj._row.end(); ++it)
		{
			out << "#";
		}
		return out;
	}
	T operator [](size_t);
	void truncate(T, T);
	void untruncate();
	int find(T);
	pair<T, int> Shensted_insert(T);                               //Classical row bumping
	T pop();                                            //Delete the bigest element and return it
private:
	vector<T> _row;
	T _left_bound, _right_bound;
};

template<class T>
class Tableau                                           // Young Tableau
{
public:
	Tableau() :
		_size(0)
	{}
	vector<int> push(T);                                        //Insert an element in the tableau
	void insert(size_t, T);                             //Tnsert an element in the row of the tableau
	void push(T *, size_t);                             //Insert several elements in given order
	friend ostream & operator<<(                        //Print the tableau
		ostream & out,
		Tableau<T> & T
		)
	{
		out << "[";
		for (auto it = T._tableau.begin(); it != T._tableau.end(); ++it)
		{
			auto it_ = it;
			if (it->size() != 0)
			{
				if (++it_ == T._tableau.end())
				{
					out << *it;
				}
				else
				{
					out << *it << ", ";
				}
			}
		}
		out << "]";
		return out;
	}
	Row<T> & operator [](size_t);
	friend void print_collection_of_Tableau(
		vector<Tableau<T>>);                            //Print the collection of tableaux
	size_t size();
	size_t height();
	size_t length();
	void truncate(T, T);
	void untruncate();
	T pop(size_t);                                      //Delete the bigest an element from the row
	T erase(size_t);                                    //Reverse bumping from the tableau
	pair<int, int> find(T);                             //Return the minimal number of a row which contains the element or -1 if there is not such a row 
	void type(size_t *);
private:
	vector<Row<T>> _tableau;
	size_t _size;
};

template<class T>
class PQ_tableaux                                       //Pair of recording and numerating Young tableaux
{
public:
	vector <int> push(T);                                       //Insert the element in inserting tableau and its counting number in recording tableau
	void push(T *, size_t n);                           //Insert several elements in given order in the way describing ...
	T erase();                                          //Reverse bumping from the pair of tableaux
	friend ostream & operator<<(                        //Print the pair of tableaux 
		ostream & out, 
		PQ_tableaux<T> & PQ
		)
	{
		out << "[" << PQ._P << ", " << PQ._Q << "]";
		return out;
	}
	void truncate(T, T);
	void untruncate();
	void showQ();                                       //Print numerating tableau
	void showP();                                       //Print recording tableau
	//void write_for_py();
	size_t size();										//Return size of tableau
	size_t height();
	size_t length();
	pair<int, int> find(T);                                        //Return the least row containing given element
	void type(size_t *);                                //Put the type of tableau in given array
	Tableau<T> & P();
private:
	Tableau<T> _P;
	Tableau<size_t> _Q;
	vector <size_t> _row_number;
};



//implementation


//class Row
template<typename T>                 Row<T>::Row(T elem)
{
	_left_bound = -INF;
	_right_bound = INF;
	this->_row.push_back(elem);
}
template<typename T>                 Row<T>::Row(T *row, size_t n) 
{	
	_left_bound = -INF;
	_right_bound = INF;
	_row.assign(n);
	for (size_t i = 0; i < n; ++i)
		_row[i] = row[i];
}
template<typename T> T               Row<T>::reverse_Shensted_insert(T x)
{
	size_t ind = --lover_bound(x);
	double new_x = _row[ind];
	_row[ind] = x;
	return new_x;
}
template<typename T> pair<T,int>   Row<T>::Shensted_insert(T x)
{
	size_t left = 0, right = _row.size();
	if (_row.empty())
	{
		_row.push_back(x);
		return -1;
	}
	size_t ind = upper_bound(x);
	if (ind == _row.size())
	{
		_row.push_back(x);
		return -1;
	}
	T new_x = _row[ind];
	_row[ind] = x;
	return make_pair(new_x, ind);
}
template<typename T> size_t          Row<T>::lower_bound(T x)
{
	size_t left = 0, right = _row.size();
	while (left < right - 1)
	{
		size_t mid = (left + right) / 2;
		if (_row[mid] < x)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if (_row[0] >= x)
		return 0;
	return right;
}
template<typename T> size_t          Row<T>::upper_bound(T x)
{
	size_t left = 0, right = _row.size();
	while (left < right - 1)
	{
		size_t mid = (left + right) / 2;
		if (_row[mid] <= x)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if (_row[0] >= x)
		return 0;
	return right;
}
template<typename T> T               Row<T>::pop()
{
	auto elem = *(--_row.end());
	_row.pop_back();
	return elem;
}
template<typename T> T               Row<T>::operator [](size_t n)
{
	return _row[n];
}
template<typename T> int             Row<T>::find(T x)
{
	int ind = (int)lower_bound(x);
	if (_row[ind] == x)
		return ind;
	return -1;
}
template<typename T> size_t          Row<T>::size() {
	return _row.size();
}
template<typename T> void            Row<T>::truncate(T trunc_low, T trunc_upper)
{
	_left_bound = trunc_low;
	_right_bound = trunc_upper;
	return;
}
template<typename T> void            Row<T>::untruncate()
{
	_left_bound = -INF;
	_right_bound = INF;
	return;
}
/*
template<typename T>
multiset<T>::iterator Row<T>::begin()
{
	return _row.begin();
}
multiset<T>::iterator Row<T>::end()
{
	return _row.end();
}
*/

//class Tableau
template<typename T> void            print_collection_of_Tableau(vector<Tableau<T>> vect_T)
{
	size_t max_height = 0;
	for (auto it : vect_T)
	{
		max_height = max(max_height, it.size());
	}
	for (int tmp_row = 0; tmp_row < max_height; ++tmp_row)
	{
		for (auto it : vect_T)
		{

		}
	}
}
template<typename T> vector<int>          Tableau<T>::push(T elem)
{
	vector<int> trace
	for (auto & it : _tableau)
	{

		auto elem_and_pos = it.Shensted_insert(elem);
		elem = elem_and_pos.first
		pos = elem_and_pos.second
		trace.push_back(pos)
		if (new_elem == -1)
			break;
		row++;
	}
	if (elem != -1)
	{
		Row<T> row(elem);
		_tableau.push_back(Row<T>(elem));
		trace.push_back(0)
	}
	_size++;
	return trace;
}
template<typename T> void            Tableau<T>::insert(size_t row, T x)
{
	if (row >= _tableau.size())
		_tableau.push_back(Row<T>());
	_tableau[row].Shensted_insert(x).first;
	_size++;
	return;
}
template<typename T> void            Tableau<T>::push(T *elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
}
template<typename T> T               Tableau<T>::pop(size_t row)
{
	return _tableau[row].pop();
}
template<typename T> T               Tableau<T>::erase(size_t tmp_row)
{
	double tmp_x = pop(tmp_row);
	for (int i = (int)tmp_row - 1; i >= 0; --i)
	{
		tmp_x = _tableau[i].reverse_Shensted_insert(tmp_x);
	}
	return tmp_x;
}
template<typename T> pair<int, int>  Tableau<T>::find(T x)
{
	for (size_t i = 0; i < _tableau.size(); ++i)
	{
		int ind = _tableau[i].find(x);
		if (ind >= 0)
		{
			return mp(i, ind);
		}
	}
	return mp((int)-1, (int)-1);
}
template<typename T> size_t          Tableau<T>::size()
{
	return _size;
}
template<typename T> size_t          Tableau<T>::height()
{
	return _tableau.size();
}
template<typename T> size_t          Tableau<T>::length()
{
	if (_tableau.empty())
	{
		return 0;
	}
	return _tableau[0].size();
}
template<typename T> void            Tableau<T>::type(size_t *type)
{
	type = new size_t[_tableau.size()];
	for (size_t i = 0; i < _tableau.size(); ++i)
	{
		type[i] = _tableau[i].size();
	}
	return;
}
template<typename T> void            Tableau<T>::truncate(T trunc_low, T trunc_upper)
{
	for (auto it = _tableau.begin(); it != _tableau.end(); ++it)
	{
		it->truncate(trunc_low, trunc_upper);
	}
	return;
}
template<typename T> void            Tableau<T>::untruncate()
{
	for (auto it : _tableau)
	{
		it.untruncate();
	}
	return;
}
template<typename T> Row<T> &        Tableau<T>::operator [](size_t i)
{
	return _tableau[i];
}

//class PQ_tableaux
template<typename T> vector<int>            PQ_tableaux<T>::push(T elem)
{
	trace = _P.push(elem).size() - 1;
	size_t changed_row = trace.size()-1;
	size_t size = _P.size();
	_Q.insert(changed_row, size);
	_row_number.push_back(changed_row);
	return trace
}
template<typename T> void            PQ_tableaux<T>::push(T *elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
}
template<typename T> T               PQ_tableaux<T>::erase()
{
	if (_row_number.empty())
	{
		cerr << "Try to delete element from empty tableau.\n";
		return 0;
	}
	size_t tmp_row = _row_number[_row_number.size() - 1];
	T new_x = _P.erase(tmp_row);
	_Q.pop(tmp_row);
	_row_number.pop_back();
	return new_x;
}
template<typename T> pair<int, int>  PQ_tableaux<T>::find(T x)
{
	return(_P.find(x));
}
template<typename T> void            PQ_tableaux<T>::type(size_t * type)
{
	_P.type(type);
	return;
}
template<typename T> size_t          PQ_tableaux<T>::size()
{
	return _P.size();
}
template<typename T> size_t          PQ_tableaux<T>::height()
{
	return _P.height();
}
template<typename T> size_t          PQ_tableaux<T>::length()
{
	return _P.length();
}
template<typename T> void            PQ_tableaux<T>::showQ()
{
	cout << _Q;
	//cout << "Q:\n" << _Q;
}
template<typename T> void            PQ_tableaux<T>::showP()
{
	cout << _P;
	//cout << "P:\n" << _P;
}
template<typename T> void            PQ_tableaux<T>::truncate(T trunc_low, T trunc_upper)
{
	_P.truncate(trunc_low, trunc_upper);
	return;
}
template<typename T> void            PQ_tableaux<T>::untruncate()
{
	_P.untruncate();
	return;
}
template<typename T> Tableau<T> &    PQ_tableaux<T>::P()
{
	return _P;
}
/*
template<typename T> void write_for_py()
{
	size_t N = _P.size();
	cout << "[";
	for (size_t i = 0; i < N; ++i)
	{
		PQ.push(r[i]);
		cout << "[";
		for (size_t j = 0; j < PQ)
		cout << ", ";
		PQ.showQ();
		if (i == N - 1)
		{
			cout << "]";
		}
		else
		{
			cout << "], ";
		}
	}
	cout << "]\n";

}
*/