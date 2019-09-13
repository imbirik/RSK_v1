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
	Row() {}
	Row(T);                                             //Class constructor
	Row(T*, size_t n);                                 //Class constructor
	size_t size();                                      //Return size of row
	pair<T, size_t> Shensted_insert(
		T,
		size_t r_bnd
	);                                                  //Classical row bumping            
	T reverse_Shensted_insert(T);                       //Reverse bumping (doesn't work)
	size_t lower_bound(T, size_t, size_t);              //Return index of the least number which is equal to or greater than an element in ginen range
	size_t upper_bound(T, size_t, size_t);              //Return index of the least number which is greater than an element in given range
	friend ostream& operator<<(                         //Printing the row
		ostream& out,
		Row<T>& obj
		)
	{
		out << setprecision(6) << fixed;
		for (auto it = obj._row.begin(); it != obj._row.end(); ++it)
		{
			out << *it << "   \t";
		}
		return out;
	}
	T operator [](size_t);                              //Return value by index
	int find(T);                                        //Return index of an element in the row or -1
	T pop();                                            //Delete the bigest element and return it
	void print_for_python();
private:
	vector<T> _row;
};


template<class T>
class Tableau                                           // Young Tableau
{
public:
	Tableau() :
		_size(0),
		_tableau(vector<Row<T>>(1)) {}
	vector<size_t> & push(T);                           //Insert an element in the tableau
	void insert(size_t, T);                             //Tnsert an element in the row of the tableau
	void push(T*, size_t);                              //Insert several elements in given order
	friend ostream& operator<<(                         //Print the tableau
		ostream& out,
		Tableau<T>& T
		)
	{
		for (auto it = T._tableau.begin(); it != T._tableau.end(); ++it)
		{
			out << *it << "\n";
		}
		return out;
	}
	Row<T> & operator [](size_t);
	friend void print_collection_of_Tableau(
		vector<Tableau<T>>);                            //Print the collection of tableaux
	size_t size();                                      //Return size of YT
	size_t height();                                    //Return height of YT
	size_t length();                                    //Return length of YT
	T pop(size_t);                                      //Delete the bigest an element from the row
	T erase(size_t);                                    //Reverse bumping from the tableau
	pair<int, int> find(T);                             //Return the minimal number of a row which contains the element or -1 if there is not such a row 
	void type(size_t*);                                 //Return the type of YT (diagram)
	void trunc(T, T);                                   //Print truncated YT
	void print_for_python();                            //Print with brackets and commas
private:
	vector<Row<T>> _tableau;
	size_t _size;
};


template<class T> class PQ_tableaux                     //Pair of recording and numerating Young tableaux
{
public:
	vector<size_t> & push(T);                           //Insert the element in inserting tableau and its counting number in recording tableau
	void push(T*, size_t n);                            //Insert several elements in given order in the way describing ...
	T erase();                                          //Reverse bumping from the pair of tableaux
	friend ostream& operator<<(                         //Print the pair of tableaux 
		ostream& out,
		PQ_tableaux<T>& PQ
		)
	{
		out << "P:\n" << PQ._P << "Q:\n" << PQ._Q;
		return out;
	}
	void showQ();                                       //Print numerating tableau
	void showP();                                       //Print recording tableau
	size_t size();										//Return size of tableau
	size_t height();                                    //Return height
	size_t length();                                    //Return length
	pair<int, int> find(T);                             //Return the least row containing given element
	void type(size_t*);                                 //Put the type of tableau in given array
	Tableau<T>& P();
	Tableau<T>& Q();
	void trunc(T, T);                                   //Return truncated YT
	void print_for_python();                            //Print with brackets and commas
private:
	Tableau<T> _P;
	Tableau<size_t> _Q;
	vector <size_t> _row_number;
};



//implementation


//class Row
template<typename T>                   Row<T>::Row(T elem)
{
	_left_bound = -INF;
	_right_bound = INF;
	this->_row.push_back(elem);
}
template<typename T>                   Row<T>::Row(T* row, size_t n)
{
	_left_bound = -INF;
	_right_bound = INF;
	_row.assign(n);
	for (size_t i = 0; i < n; ++i)
		_row[i] = row[i];
}
template<typename T> T                 Row<T>::reverse_Shensted_insert(T x)
{
	size_t ind = --lover_bound(x);
	double new_x = _row[ind];
	_row[ind] = x;
	return new_x;
}
template<typename T> pair<T, size_t>   Row<T>::Shensted_insert(T x, size_t r_bnd)
{
	r_bnd = min(r_bnd, size());
	if (_row.empty())
	{
		_row.push_back(x);
		return mp(-1, 0);
	}
	size_t ind = upper_bound(x, 0, r_bnd);
	if (ind == _row.size())
	{
		_row.push_back(x);
		return mp(-1, _row.size());
	}
	T new_x = _row[ind];
	_row[ind] = x;
	return mp(new_x, ind + 1);
}
template<typename T> size_t            Row<T>::lower_bound(T x, size_t l_bnd, size_t r_bnd)
{
	int left = max((int)l_bnd, (int)0), right = min((int)r_bnd, (int)size());
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
template<typename T> size_t            Row<T>::upper_bound(T x, size_t l_bnd, size_t r_bnd)
{
	int left = max((int)l_bnd, (int)0), right = min((int)r_bnd, (int)size());
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
	if (_row[0] > x)
		return 0;
	return right;
}
template<typename T> T                 Row<T>::pop()
{
	auto elem = *(--_row.end());
	_row.pop_back();
	return elem;
}
template<typename T> T                 Row<T>::operator [](size_t n)
{
	return _row[n];
}
template<typename T> int               Row<T>::find(T x)
{
	int ind = (int)lower_bound(x);
	if (_row[ind] == x)
		return ind;
	return -1;
}
template<typename T> size_t            Row<T>::size() {
	return _row.size();
}
template<typename T> void              Row<T>::print_for_python()
{
	cout << "[";
	for (int i = 0; i < _row.size() - 1; i++)
		cout << _row[i] << ", ";
	cout << _row[_row.size() - 1] << "]";
}


//class Tableau
template<typename T> void              print_collection_of_Tableau(vector<Tableau<T>> vect_T)
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
template<typename T> vector<size_t> &  Tableau<T>::push(T elem)
{
	T new_elem = elem;
	vector<int> trace;
	for (auto& it : _tableau)
	{
		auto elem_and_pos = it.Shensted_insert(new_elem);
		new_elem = elem_and_pos.first;
		auto pos = elem_and_pos.second;
		trace.push_back(pos);
		if (new_elem == -1)
			break;
	}
	if (new_elem != -1)
	{
		Row<T> row(new_elem);
		_tableau.push_back(Row<T>(new_elem));
		trace.push_back(0);
	}
	_size++;
	return trace;
}
template<typename T> void              Tableau<T>::insert(size_t row, T x)
{
	if (row >= _tableau.size())
		_tableau.push_back(Row<T>());
	_tableau[row].Shensted_insert(x).first;
	_size++;
	return;
}
template<typename T> void              Tableau<T>::push(T* elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
}
template<typename T> T                 Tableau<T>::pop(size_t row)
{
	return _tableau[row].pop();
}
template<typename T> T                 Tableau<T>::erase(size_t tmp_row)
{
	double tmp_x = pop(tmp_row);
	for (int i = (int)tmp_row - 1; i >= 0; --i)
	{
		tmp_x = _tableau[i].reverse_Shensted_insert(tmp_x);
	}
	return tmp_x;
}
template<typename T> pair<int, int>    Tableau<T>::find(T x)
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
template<typename T> size_t            Tableau<T>::size()
{
	return _size;
}
template<typename T> size_t            Tableau<T>::height()
{
	return _tableau.size();
}
template<typename T> size_t            Tableau<T>::length()
{
	if (_tableau.empty())
	{
		return 0;
	}
	return _tableau[0].size();
}
template<typename T> void              Tableau<T>::type(size_t* type)
{
	type = new size_t[_tableau.size()];
	for (size_t i = 0; i < _tableau.size(); ++i)
	{
		type[i] = _tableau[i].size();
	}
	return;
}
template<typename T> void              Tableau<T>::trunc(T left_bound, T right_bound)
{
	cout << setprecision(6) << fixed;
	for (size_t i = 0; i < height(); ++i)
		for (size_t j = 0; j < _tableau[i].size(); ++j)
			if (_tableau[i][j] <= left_bound)
				cout << space8 << "   \t";
			else if (_tableau[i][j] <= right_bound)
				cout << _tableau[i][j] << "   \t";
}
template<typename T> Row<T>&           Tableau<T>::operator [](size_t i)
{
	return _tableau[i];
}
template<typename T> void 		 	   Tableau<T>::print_for_python()
{
	cout << "[";
	for (int i = 0; i < _tableau.size() - 1; i++) {
		_tableau[i].print_for_python();
		cout << ", ";
	}
	_tableau[_tableau.size() - 1].print_for_python();
	cout << "]";
}


//class PQ_tableaux
template<typename T> vector<int> &     PQ_tableaux<T>::push(T elem)
{
	auto trace = _P.push(elem);
	size_t changed_row = trace.size() - 1;
	size_t size = _P.size();
	_Q.insert(changed_row, size);
	_row_number.push_back(changed_row);
	return trace;
}
template<typename T> void              PQ_tableaux<T>::push(T* elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
}
template<typename T> T                 PQ_tableaux<T>::erase()
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
template<typename T> pair<int, int>    PQ_tableaux<T>::find(T x)
{
	return(_P.find(x));
}
template<typename T> void              PQ_tableaux<T>::type(size_t* type)
{
	_P.type(type);
	return;
}
template<typename T> size_t            PQ_tableaux<T>::size()
{
	return _P.size();
}
template<typename T> size_t            PQ_tableaux<T>::height()
{
	return _P.height();
}
template<typename T> size_t            PQ_tableaux<T>::length()
{
	return _P.length();
}
template<typename T> void              PQ_tableaux<T>::showQ()
{
	cout << _Q;
	//cout << "Q:\n" << _Q;
}
template<typename T> void              PQ_tableaux<T>::showP()
{
	cout << _P;
	//cout << "P:\n" << _P;
}
template<typename T> void              PQ_tableaux<T>::truncate(T trunc_low, T trunc_upper)
{
	_P.truncate(trunc_low, trunc_upper);
	return;
}
template<typename T> void              PQ_tableaux<T>::untruncate()
{
	_P.untruncate();
	return;
}
template<typename T> Tableau<T>&       PQ_tableaux<T>::P()
{
	return _P;
}
template<typename T> void              PQ_tableaux<T>::print_for_python()
{
	cout << "[";
	_P.print_for_python();
	cout << ", ";
	_Q.print_for_python();
	cout << "]";
}
template<typename T> void              PQ_tableaux<T>::trunc(T left_bound, T right_bound)
{
	for (size_t i = 0; i < height(); ++i)
		for (size_t j = 0; j < _P._tableau[i].size(); ++j)
			if (_P._tableau[i][j] <= left_bound)
				cout << ' ';
			else if (_P.tableau[i][j] <= right_bound)
				cout << '#';
			else
				cout << '0';
}
