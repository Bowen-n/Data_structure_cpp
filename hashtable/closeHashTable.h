#pragma once
#include "dynamicSearchTable.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

// closeHashTable class
template <class KEY, class OTHER>
class closeHashTable :public dynamicSearchTable<KEY, OTHER> {
	// cout<<
	template<class KEY, class OTHER>
	friend ostream& operator<<(ostream &, closeHashTable<KEY, OTHER>&);
private:
	// node in table
	struct node {
		SET <KEY, OTHER> data;
		int state; // 0-empty; 1-active; 2-deleted

		node() :state(0) {};
	};

	node *array;
	int size;

	// function pointer
	int(*key)(const KEY &x);
	static int defaultKey(const int &x) { return x; }

public:
	closeHashTable(int length = 101, int(*f)(const KEY &x) = defaultKey);
	~closeHashTable() { delete[]array; }
	SET<KEY, OTHER>*find(const KEY&x)const;
	SET<KEY, OTHER>*find(const KEY&x, int &find_time)const;
	void insert(const SET<KEY, OTHER> &x);
	void insert(const SET<KEY, OTHER> &x, int &conflict);
	void remove(const KEY &x);
	//void display()const;
};

// implementation
#include "closeHashTable_imp.h"