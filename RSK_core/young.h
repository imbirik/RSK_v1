//7 October 2019


#pragma once
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include "permutations.h"
#include "random.h"
#define space8 "        "
#define INF (int)1e8
#define mp make_pair
#define coord pair<size_t, size_t>

using namespace std;

template<class T> class Row                                     //Row of Young tableau
{
public:

	//class constructors
	Row() {}
	Row(T);                                                     //Class constructor
	Row(T*, size_t n);                                          //Class constructor

	//friend operators 
	friend ostream& operator<<(                                 //Printing the row
		ostream& out,
		const Row<T>& obj
		)
	{
		out << setprecision(6) << fixed;
		for (auto it = obj._row.begin(); it != obj._row.end(); ++it)
		{
			out << *it << "   \t";
		}
		return out;
	}

	//non-constant operators
	pair<T, size_t>   Shensted_insert(T, size_t r_bnd);   //Classical row bumping            
	T                 reverse_Shensted_insert(T);   //Reverse bumping (doesn't work)
	const T& pop();   //Delete the bigest element and return it

	//constant operators
	size_t            lower_bound(T, size_t, size_t)   const;   //Return index of the least number which is equal to or greater than an element in ginen range
	size_t            upper_bound(T, size_t, size_t)   const;   //Return index of the least number which is greater than an element in given range
	size_t            size()                           const;   //Return size of row
	const T& operator [](size_t)              const;   //Return value by index
	size_t            find(T)                          const;   //Return index of an element in the row or -1
	void              print_for_python()               const;
private:
	vector<T> _row;
};


template<class T> class Tableau                         // Young Tableau
{
public:

	//class constructors
	Tableau() :
		_size(0),
		_tableau(vector<Row<T>>(1)) {}

	//friend operators
	friend ostream& operator<<(                         //Print the tableau
		ostream& out,
		const Tableau<T>& T
		)
	{
		for (auto it = T._tableau.begin(); it != T._tableau.end(); ++it)
		{
			out << *it << "\n";
		}
		return out;
	}
	friend bool operator ==(                        //Compare two tableaux
		Tableau<T> T1,
		Tableau<T> T2)
	{
		for (size_t i = 0; i < T1.height(); ++i)
		{
			for (size_t j = 0; j < T1[i].size(); ++j)
			{
				if (T1[i][j] != T2[i][j])
					return false;
			}
		}
		return true;
	}
	friend bool operator !=(                        //Compare two tableaux
		Tableau<T> T1,
		Tableau<T> T2)
	{
		return !(T1 == T2);
	}

	//non-constant methods
	size_t          push(T);                           //Insert an element in the tableau
	size_t          push(T, coord&);                   //Insert an element in the tableau with tracking given cell
	void            insert(size_t, T);                 //Tnsert an element in the row of the tableau
	void            push(T*, size_t);                  //Insert several elements in given order
	void            push(T*, size_t, coord, coord*);
	T               pop(size_t);                       //Delete the bigest an element from the row
	T               erase(size_t);                     //Reverse bumping from the tableau
	void            trunc(T, T);                       //Print truncated YT

	//constant methods
	const Row<T>& operator[] (size_t)   const;
	size_t          size()                const;   //Return size of YT
	size_t          height()              const;   //Return height of YT
	size_t          length()              const;   //Return length of YT
	coord           find(T)               const;   //Return the minimal number of a row which contains the element or -1 if there is not such a row 
	void            form(size_t*)         const;   //Return the type of YT (diagram)
	void            print_for_python()    const;   //Print with brackets and commas
private:
	vector<Row<T>> _tableau;
	size_t _size;
};


template<class T> class PQ_tableaux                        //Pair of recording and numerating Young tableaux
{
public:

	//friend operators
	friend ostream& operator<<(                            //Print the pair of tableaux 
		ostream& out,
		PQ_tableaux<T>& PQ
		)
	{
		out << "P:\n" << PQ._P << "Q:\n" << PQ._Q;
		return out;
	}

	//non-constant methods
	void    push(T);   //Insert the element in inserting tableau and its counting number in recording tableau
	void    push(T, coord&);   //Insert the element in inserting tableau and its counting number in recording tableau
	void    push(T*, size_t n);   //Insert several elements in given order in the way describing ...
	void    push(T*, size_t, coord, coord*);
	T& erase();   //Reverse bumping from the pair of tableaux
	void    trunc(T, T);   //Return truncated YT

	//constant methods
	void                     showQ()              const;   //Print numerating tableau
	void                     showP()              const;   //Print recording tableau
	size_t                   size()               const;   //Return size of tableau
	size_t                   height()             const;   //Return height
	size_t                   length()             const;   //Return length
	coord                    find(T)              const;   //Return the least row containing given element
	void                     form(size_t*)        const;   //Put the type of tableau in given array
	const Tableau<T>& P()                  const;
	const Tableau<size_t>& Q()                  const;
	void                     print_for_python()   const;   //Print with brackets and commas
private:
	Tableau<T> _P;
	Tableau<size_t> _Q;
	vector <size_t> _row_number;
};


const long long P = 37, MOD = (long long)1e9 + 9;

template <typename T> class hash<Tableau<T>> {
public:
	size_t operator()(const Tableau<T>& tableau) const
	{
		long long EXP = 1, HASH = 0;
		size_t* type = new size_t[tableau.height()];
		tableau.type(type);
		for (size_t i = 0; i < tableau.height(); ++i)
		{
			HASH += (long long)type[i] * EXP;
			EXP = EXP * P % MOD;
		}
		for (size_t i = 0; i < tableau.height(); ++i)
		{
			for (size_t j = 0; j < tableau[i].size(); ++j)
			{
				HASH += tableau[i][j] * EXP;
				EXP = EXP * P % MOD;
			}
		}
		return (size_t)(HASH % MOD);
	}
};
template <typename T> class hash<pair<Tableau<T>, Tableau<T>>>
{
public:
	size_t operator ()(const pair<Tableau<T>, Tableau<T>>& tableau_pair) const
	{
		long long EXP = 1;
		for (size_t i = 0; i < tableau_pair.first.height() + tableau_pair.first.size(); ++i)
			EXP = EXP * P % MOD;
		return hash<Tableau<T>>()(tableau_pair.first) + (size_t)EXP * hash<Tableau<T>>()(tableau_pair.second);
	}
};

//implementation


//class Row

//class constructors
template<typename T>   Row<T>::Row(T elem)
{
	this->_row.push_back(elem);
}
template<typename T>   Row<T>::Row(T* row, size_t n)
{
	_row.assign(n);
	for (size_t i = 0; i < n; ++i)
		_row[i] = row[i];
}

//non-constant methods
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
		return mp(-1, ind);
	}
	T new_x = _row[ind];
	_row[ind] = x;
	return mp(new_x, ind);
}
template<typename T> const T& Row<T>::pop()
{
	auto elem = *(--_row.end());
	_row.pop_back();
	return elem;
}

//constant methods
template<typename T> size_t     Row<T>::lower_bound(T x, size_t l_bnd, size_t r_bnd)   const
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
template<typename T> size_t     Row<T>::upper_bound(T x, size_t l_bnd, size_t r_bnd)   const
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
template<typename T> const T& Row<T>::operator [](size_t n)                          const
{
	if (size() > n)
		return _row[n];
	return -1;
}
template<typename T> size_t     Row<T>::find(T x)                                      const
{
	int ind = (int)lower_bound(x);
	if (_row[ind] == x)
		return ind;
	return (size_t)-1;
}
template<typename T> size_t     Row<T>::size()                                         const {
	return _row.size();
}
template<typename T> void       Row<T>::print_for_python()                             const
{
	cout << "[";
	for (int i = 0; i < _row.size() - 1; i++)
		cout << _row[i] << ", ";
	cout << _row[_row.size() - 1] << "]";
}


//class Tableau

//external functions
template<typename T> void   print_collection_of_Tableau(vector<Tableau<T>> vect_T)
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

//non-constant methods
template<typename T> inline size_t                Tableau<T>::push(T elem)
{
	T new_elem = elem;
	size_t row = 0;
	for (auto& it : _tableau)
	{
		pair<T, size_t> elem_and_pos = it.Shensted_insert(new_elem, it.size());
		new_elem = elem_and_pos.first;
		size_t pos = elem_and_pos.second;
		if (new_elem == -1)
			break;
		row++;
	}
	if (new_elem != -1)
	{
		Row<T> row(new_elem);
		_tableau.push_back(Row<T>(new_elem));
	}
	_size++;
	return row;
}
template<typename T> inline size_t   Tableau<T>::push(T elem, coord& cell)
{
	T new_elem = elem;
	size_t* trace = new size_t[height() + 1];
	size_t cnt = 0;
	for (auto& it : _tableau)
	{
		pair<T, size_t> elem_and_pos = it.Shensted_insert(new_elem, it.size());
		new_elem = elem_and_pos.first;
		size_t pos = elem_and_pos.second;
		trace[cnt++] = pos;
		if (new_elem == -1)
			break;
	}
	if (new_elem != -1)
	{
		Row<T> row(new_elem);
		_tableau.push_back(Row<T>(new_elem));
		trace[cnt] = 0;
	}
	else
		cnt--;
	_size++;
	if (cnt >= cell.second && trace[cell.second] == cell.first) //?????????????
	{
		cell = mp(trace[cell.second + 1], cell.second + 1);
		delete[] trace;
		return cnt;
	}
	delete[] trace;
	return cnt;
}
template<typename T> void                  Tableau<T>::insert(size_t row, T x)
{
	if (row >= _tableau.size())
		_tableau.push_back(Row<T>());
	_tableau[row].Shensted_insert(x, _tableau[row].size());
	_size++;
	return;
}
template<typename T> void                  Tableau<T>::push(T* elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
	return;
}
template<typename T> void                  Tableau<T>::push(T* elems, size_t n, coord cell, coord* track)
{
	track[0] = cell;
	for (size_t i = 0; i < n; ++i)
	{
		track[i + 1] = push(elems[i], track[i]);
	}
	return;
}
template<typename T> T                     Tableau<T>::pop(size_t row)
{
	return _tableau[row].pop();
}
template<typename T> T                     Tableau<T>::erase(size_t tmp_row)
{
	double tmp_x = pop(tmp_row);
	for (int i = (int)tmp_row - 1; i >= 0; --i)
	{
		tmp_x = _tableau[i].reverse_Shensted_insert(tmp_x);
	}
	return tmp_x;
}
template<typename T> void                  Tableau<T>::trunc(T left_bound, T right_bound)
{
	cout << setprecision(6) << fixed;
	for (size_t i = 0; i < height(); ++i)
		for (size_t j = 0; j < _tableau[i].size(); ++j)
			if (_tableau[i][j] <= left_bound)
				cout << space8 << "   \t";
			else if (_tableau[i][j] <= right_bound)
				cout << _tableau[i][j] << "   \t";
}

//constant methods
template<typename T> coord           Tableau<T>::find(T x)              const
{
	for (size_t i = 0; i < _tableau.size(); ++i)
	{
		int ind = _tableau[i].find(x);
		if (ind >= 0)
		{
			return mp(i, ind);
		}
	}
	return mp((size_t)-1, (size_t)-1);
}
template<typename T> size_t          Tableau<T>::size()                 const
{
	return _size;
}
template<typename T> size_t          Tableau<T>::height()               const
{
	return _tableau.size();
}
template<typename T> size_t          Tableau<T>::length()               const
{
	if (_tableau.empty())
	{
		return 0;
	}
	return _tableau[0].size();
}
template<typename T> void            Tableau<T>::form(size_t* form)     const
{
	for (size_t i = 0; i < _tableau.size(); ++i)
	{
		form[i] = _tableau[i].size();
	}
	return;
}
template<typename T> const Row<T>& Tableau<T>::operator[](size_t i)   const
{
	if (height() > i)
		return _tableau[i];
	return *(new Row<T>());

}
template<typename T> void            Tableau<T>::print_for_python()     const
{
	cout << "[";
	for (int i = 0; i < height() - 1; i++) {
		_tableau[i].print_for_python();
		cout << ", ";
	}
	_tableau[height() - 1].print_for_python();
	cout << "]";
}


//class PQ_tableaux

//non-constant methods
template<typename T> void    PQ_tableaux<T>::push(T elem)
{
	size_t changed_row = _P.push(elem);
	_Q.insert(changed_row, _P.size());
	_row_number.push_back(changed_row);
	return;
}
template<typename T> void    PQ_tableaux<T>::push(T elem, coord& cell)
{
	size_t row = _P.push(elem, cell);
	_Q.insert(row, _P.size());
	_row_number.push_back(row);
	return;
}
template<typename T> void    PQ_tableaux<T>::push(T* elems, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push(elems[i]);
	}
}
template<typename T> void    PQ_tableaux<T>::push(T* elems, size_t n, coord cell, coord* track)
{
	track[0] = cell;
	for (size_t i = 0; i < n; ++i)
	{
		track[i + 1] = push(elems[i], track[i]);
	}
	return;
}

template<typename T> T& PQ_tableaux<T>::erase()
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
template<typename T> void    PQ_tableaux<T>::trunc(T left_bound, T right_bound)
{
	for (size_t i = 0; i < height(); ++i)
	{
		for (size_t j = 0; j < _P._tableau[i].size(); ++j)
		{
			if (_P._tableau[i][j] <= left_bound)
			{
				cout << ' ';
			}
			else if (_P.tableau[i][j] <= right_bound)
			{
				cout << '#';
			}
			else
			{
				cout << '0';
			}
		}
	}
}

//constant methods
template<typename T> coord                    PQ_tableaux<T>::find(T x)            const
{
	return(_P.find(x));
}
template<typename T> void                     PQ_tableaux<T>::form(size_t* form)   const
{
	_P.form(form);
	return;
}
template<typename T> size_t                   PQ_tableaux<T>::size()               const
{
	return _P.size();
}
template<typename T> size_t                   PQ_tableaux<T>::height()             const
{
	return _P.height();
}
template<typename T> size_t                   PQ_tableaux<T>::length()             const
{
	return _P.length();
}
template<typename T> void                     PQ_tableaux<T>::showQ()              const
{
	cout << _Q;
	//cout << "Q:\n" << _Q;
}
template<typename T> void                     PQ_tableaux<T>::showP()              const
{
	cout << _P;
	//cout << "P:\n" << _P;
}
template<typename T> const Tableau<T>& PQ_tableaux<T>::P()                  const
{
	return _P;
}
template<typename T> const Tableau<size_t>& PQ_tableaux<T>::Q()                  const
{
	return _Q;
}
template<typename T> void                     PQ_tableaux<T>::print_for_python()   const
{
	cout << "[";
	_P.print_for_python();
	cout << ", ";
	_Q.print_for_python();
	cout << "]";
}
