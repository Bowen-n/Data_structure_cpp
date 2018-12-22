#pragma once
#include "dynamicSearchTable.h"
#include <cassert>
template <class KEY, class OTHER>
class openHashTable :public dynamicSearchTable<KEY, OTHER> {
private:
	struct node {
		SET<KEY, OTHER>data;
		node *next;

		node(const SET<KEY, OTHER>&d, node*n = NULL) { data = d; next = n; }
		node() { next = NULL; }
	};

	node **array;
	int size;
	int(*key)(const KEY &x);
	static int defaultKey(const int &x) { return x; }

public:
	openHashTable(int length = 101, int(*f)(const KEY&x) = defaultKey);
	~openHashTable();
	SET<KEY, OTHER>*find(const KEY &x)const;
	SET<KEY, OTHER>*find(const KEY &x, int &find_time)const;
	void insert(const SET<KEY, OTHER>&x);
	void remove(const KEY &x);

};

// implementation
#include "openHashTable_imp.h"
