#pragma once
#pragma once

// insert sort
template <class T>
void simpleInsertSort(T a[], int size, int &move, int &compare) {
	int k;
	T tmp;

	for (int j = 1; j < size; j++) {
		tmp = a[j];
		++move;
		for (k = j - 1; k >= 0; --k) {
			if (tmp < a[k]) {
				a[k + 1] = a[k];
				++compare;
				++move;
			}
			else {
				++compare;
				break;
			}
		}
		a[k + 1] = tmp;
		++move;
	}
}

// bubble sort
template <class T>
void bubbleSort(T a[], int size, int &move, int &compare) {
	int i, j;

	T tmp;
	bool flag = true;

	for (i = 1; i < size && flag; i++) {
		flag = false;
		for (j = 0; j < size - i; j++) {
			if (a[j + 1] < a[j]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				flag = true;
				move += 3;
				++compare;
			}
			else {
				++compare;
			}
		}
	}
}

// simple select sort 
template<class T>
void simpleSelectSort(T a[], int size, int&move, int&compare) {
	int i, j, min;
	T tmp;

	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++)
			if (a[j] < a[min]) {
				min = j;
				++compare;
			}
			else
				++compare;
		tmp = a[i]; a[i] = a[min]; a[min] = tmp;
		move += 3;
	}
}

// quick sort
template<class T>
void quickSort(T a[], int low, int high, int&move, int&compare) {
	int mid;
	if (low >= high)return;
	mid = divide(a, low, high, move, compare);
	quickSort(a, low, mid - 1, move, compare);
	quickSort(a, mid + 1, high, move, compare);
}

template <class T>
void quickSort(T a[], int size, int&move, int&compare) {
	quickSort(a, 0, size - 1, move, compare);
}

template <class T>
int divide(T a[], int low, int high, int&move, int&compare) {
	T k = a[low]; ++move;
	do {
		while (low < high && a[high] >= k) { ++compare; --high; }
		if (low < high) { a[low] = a[high]; ++low; ++move; }
		while (low < high&&a[low] <= k) { ++low; ++compare; }
		if (low < high) { a[high] = a[low]; --high; ++move; }
	} while (low != high);
	a[low] = k; ++move;
	return low;
}

// shell sort
template<class T>
void shellSort(T a[], int size, int &move, int &compare) {
	int step, i, j;
	T tmp;

	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++) {
			tmp = a[i]; ++move;
			for (j = i - step; j >= 0; j -= step) {
				if (a[j] > tmp) {
					a[j + step] = a[j];
					++move; ++compare;
				}
				else {
					++compare;
					break;
				}
			}
			a[j + step] = tmp;
			++move;
		}
}

// heap sort
template<class T>
void heapSort(T a[], int size, int &move, int&compare) {
	int i;
	T tmp;

	for (i = size / 2 - 1; i >= 0; i--)
		percolateDown(a, i, size, move, compare);

	for (i = size - 1; i > 0; i--) {
		tmp = a[0]; a[0] = a[i]; a[i] = tmp;
		move += 3;
		percolateDown(a, 0, i, move, compare);
	}
}

template<class T>
void percolateDown(T a[], int hole, int size, int&move, int&compare) {
	int child;
	T tmp = a[hole]; ++move;

	for (; hole * 2 + 1 < size; hole = child) {
		child = hole * 2 + 1;
		if (child != size - 1) {
			if (a[child + 1] > a[child]) {
				child++;
				++compare;
			}
			else {
				++compare;

			}
		}
		if (a[child] > tmp) {
			a[hole] = a[child];
			++move; ++compare;
		}
		else {
			++compare;
			break;
		}
	}
	a[hole] = tmp; ++move;
}

// binary insert sort
template<class T>
void binaryInsertSort(T a[], int size, int&move, int&compare) {
	int low, high, middle;
	T tmp;

	for (int i = 1; i < size; ++i) {

		low = 0; high = i - 1; tmp = a[i]; ++move;

		while (low <= high) {
			middle = (high + low) / 2;
			if (a[middle] >= tmp) {
				high = middle - 1;
				++compare;
			}
			else {
				low = middle + 1;
				++compare;
			}
		}
		for (int j = i; j > low; --j) {
			a[j] = a[j - 1];
			++move;
		}
		a[low] = tmp;
		++move;
	}
}

// merge sort
template<class T>
void merge(T a[], int left, int mid, int right,
	int &move, int&compare) {
	T *tmp = new T[right - left + 1];

	int i = left, j = mid, k = 0;

	while (i < mid && j <= right) { // both end
		if (a[i] < a[j]) {
			tmp[k++] = a[i++];
			compare++; move++;
		}
		else {
			tmp[k++] = a[j++];
			compare++; move++;
		}
	}

	while (i < mid) {
		tmp[k++] = a[i++];
		move++;
	}
	while (j <= right) {
		tmp[k++] = a[j++];
		move++;
	}

	for (i = 0, k = left; k <= right;) {
		a[k++] = tmp[i++];
		move++;
	}
	delete[]tmp;
}

template<class T>
void mergeSort(T a[], int left, int right, int &move, int&compare) {
	int mid = (left + right) >> 1;

	if (left == right)return;

	mergeSort(a, left, mid, move, compare);
	mergeSort(a, mid + 1, right, move, compare);
	merge(a, left, mid + 1, right, move, compare);

}

template<class T>
void mergeSort(T a[], int size, int&move, int&compare) {
	mergeSort(a, 0, size - 1, move, compare);
}

