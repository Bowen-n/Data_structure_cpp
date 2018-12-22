#pragma once

template<class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int(*f)(const KEY &x))
	:size(length), key(f) {
	array = new node[size]; assert(array != NULL);
}


template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
	int initPos, pos;

	// mod method for hash function
	//initPos = pos = key(x.key) % size;
	initPos = pos = key(x.key);
	do {
		// find empty position
		if (array[pos].state != 1) {
			array[pos].data = x;
			array[pos].state = 1;
			return;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);

}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, int&conflict) {
	int initPos, pos;
	conflict = 0;
	// mod
	// initPos = pos = key(x.key) % size;
	initPos = pos = key(x.key);
	do {
		// find empty position
		if (array[pos].state != 1) {
			array[pos].data = x;
			array[pos].state = 1;
			return;
		}
		pos = (pos + 1) % size;
		++conflict;
	} while (pos != initPos);
}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x) {
	int initPos, pos;

	// mod method for hash function
	// initPos = pos = key(x) % size;
	initPos = pos = key(x);
	do {
		// not existing in the array
		if (array[pos].state == 0)return;
		// find and remove
		if (array[pos].state == 1 && array[pos].data.key == x) {
			array[pos].state = 2;
			return;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);
}

template<class KEY, class OTHER>
SET<KEY, OTHER>*closeHashTable<KEY, OTHER>::find(const KEY &x)const {
	int initPos, pos;

	// mod method for hash function
	// initPos = pos = key(x) % size;
	initPos = pos = key(x);
	do {
		// not existing
		if (array[pos].state == 0)return NULL;
		// find and return its address
		if (array[pos].state == 1 && array[pos].data.key == x)
			return (SET<KEY, OTHER>*)&array[pos];
		pos = (pos + 1) % size;
	} while (pos != initPos);
}

template<class KEY, class OTHER>
SET<KEY, OTHER>*closeHashTable<KEY, OTHER>::find(const KEY &x, int &find_time)const {
	int initPos, pos;
	find_time = 0;
	// mod
	// initPos = pos = key(x) % size;
	initPos = pos = key(x);
	do {
		// not existing
		if (array[pos].state == 0)return NULL;
		// find and return its address
		if (array[pos].state == 1 && array[pos].data.key == x)
			return (SET<KEY, OTHER>*)&array[pos];
		pos = (pos + 1) % size;
		++find_time;
	} while (pos != initPos);
}

template<class KEY, class OTHER>
ostream&operator<<(ostream &out, closeHashTable<KEY, OTHER> &obj) {
	for (int i = 0; i < obj.size; i++) {
		out << obj.array[i].data.key << "  ";
		out << obj.array[i].data.other << "  ";
		out << obj.array[i].state << endl;
	}
	return out;
}