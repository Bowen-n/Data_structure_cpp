#pragma once

// merge sort with s1
template <class T>
void merge_s1(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s1 <= a[j].s1)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with s2
template<class T>
void merge_s2(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s2 <= a[j].s2)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with s3
template<class T>
void merge_s3(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s3 <= a[j].s3)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with s4
template<class T>
void merge_s4(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s4 <= a[j].s4)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with s5
template<class T>
void merge_s5(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s5 <= a[j].s5)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with s6
template<class T>
void merge_s6(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right)
		if (a[i].s6 <= a[j].s6)tmp[k++] = a[i++];
		else tmp[k++] = a[j++];

		while (i < mid)tmp[k++] = a[i++];
		while (j <= right)tmp[k++] = a[j++];

		for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
		delete[]tmp;
}

// merge sort with total score
template<class T>
void merge_total(T a[], int left, int mid, int right) {
	T *tmp = new T[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right) {
		if (a[i].total <= a[j].total)
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}

	while (i < mid)tmp[k++] = a[i++];
	while (j <= right)tmp[k++] = a[j++];

	for (i = 0, k = left; k <= right;)a[k++] = tmp[i++];
}

template <class T>
void mergeSort(T a[], int size, int sub) {
	mergeSort(a, 0, size - 1, sub);
}

// sub represents which subject is being sorted
template<class T>
void mergeSort(T a[], int left, int right, int sub) {
	int mid = (left + right) >> 1;

	if (left == right) return;
	mergeSort(a, left, mid, sub);
	mergeSort(a, mid + 1, right, sub);
	switch (sub) {
	case 0:
		merge_total(a, left, mid + 1, right);
		break;
	case 1:
		merge_s1(a, left, mid + 1, right);
		break;
	case 2:
		merge_s2(a, left, mid + 1, right);
		break;
	case 3:
		merge_s3(a, left, mid + 1, right);
		break;
	case 4:
		merge_s4(a, left, mid + 1, right);
		break;
	case 5:
		merge_s5(a, left, mid + 1, right);
		break;
	case 6:
		merge_s6(a, left, mid + 1, right);
		break;
	default:
		break;
	}

}