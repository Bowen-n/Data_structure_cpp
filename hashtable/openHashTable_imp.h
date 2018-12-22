#pragma once

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int length, int(*f)(const KEY &x))
	:size(length), key(f) {
	array = new node*[size];
	for (int i = 0; i < size; i++)array[i] = NULL;
}

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable() {
	node *p, *q;

	for (int i = 0; i < size; i++) { 
		p = array[i];
		while (p != NULL) { 
			q = p->next;
			delete p;
			p = q;
		}
	}

	delete[]array;
}

template<class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
	int pos;
	node *p;

	pos = key(x.key);
	array[pos] = new node(x, array[pos]); // insert into the start of array[pos]
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x) {
	int pos;
	node *p, *q;

	pos = key(x);
	// not existing
	if (array[pos] == NULL)return;
	p = array[pos];
	if (array[pos]->data.key == x) {
		array[pos] = p->next;
		delete p;
		return;
	}
	while (p->next != NULL && !(p->next->data.key == x))p = p->next;
	if (p->next != NULL) { // p->(x)
		q = p->next;       // p->q(x)->..
		p->next = q->next; // p->..  q(x) is not in the linked list anymore
		delete q;          // delete q(x)
	}
}

template<class KEY, class OTHER>
SET<KEY, OTHER>*openHashTable<KEY, OTHER>::find(const KEY&x)const {
	int pos;
	node *p;

	pos = key(x);
	p = array[pos];

	while (p != NULL && !(p->data.key == x))p = p->next;
	if (p == NULL)return NULL;
	else return (SET<KEY, OTHER>*)p;
}

template<class KEY, class OTHER>
SET<KEY, OTHER>*openHashTable<KEY, OTHER>::find(const KEY&x, int&find_time)const {
	int pos; find_time = 0;
	node *p;

	pos = key(x);
	p = array[pos];

	while (p != NULL && !(p->data.key == x)) {
		p = p->next;
		++find_time;
	}
	if (p == NULL)return NULL;
	else return (SET<KEY, OTHER>*)p;
}