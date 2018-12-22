#include "Sort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iomanip>
using namespace std;

void rand_generator(int a[], int size, double rand_rate) {
	srand(2);
	if (rand_rate != -1) {
		int divide = int(size * (1 - rand_rate));
		for (int i = 0; i < divide; i++)
			a[i] = i + 1;
		for (int i = divide; i < size; i++)
			a[i] = rand() % size + 1;
	}
	else {
		for (int i = 0; i < size; i++)
			a[i] = size - i;
	}

}

int main() {

	clock_t start, end;
	cout << "Please input the length of the list:";
	int size; cin >> size;
	double rand_rate = 0;
	double endtime;
	while (true) {

		cout << endl << "rand_rate:" << rand_rate << endl;
		int *a = new int[size]; assert(a != NULL);


		rand_generator(a, size, rand_rate);
		int move = 0; int compare = 0;
		start = clock();
		simpleInsertSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "simple insert sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;

		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		bubbleSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "bubble sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		simpleSelectSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "simple select sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		quickSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "quick sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		shellSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "shell sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		heapSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "heap sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		binaryInsertSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "binary insert sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;


		rand_generator(a, size, rand_rate);
		move = 0; compare = 0;
		start = clock();
		mergeSort<int>(a, size, move, compare);
		end = clock();
		endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "merge sort:move " << move << ",compare " << compare << ",time " << endtime * 1000 << "ms" << endl;

		if (rand_rate == -1)
			break;
		rand_rate += 0.2;
		if (rand_rate == 1.2)
			rand_rate = -1;

		delete[]a;
	}
	return 0;
}