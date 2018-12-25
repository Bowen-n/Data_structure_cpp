#pragma once
#include<cstdlib>
template <class elemType>
class linkQueue {
private:
	struct node {
		elemType data;
		node *next;
		node(const elemType &x, node *n = NULL)
			:data(x), next(n) {}
		node() :next(NULL) {}
		~node() {}
	};

	node *front, *rear;

public:
	linkQueue();
	~linkQueue();
	bool isEmpty()const;
	void enQueue(const elemType &x);
	bool isinQueue(const elemType)const;
	elemType deQueue();
	elemType getHead()const;
};

// implemented in
#include "linkQueue_imp.h"
