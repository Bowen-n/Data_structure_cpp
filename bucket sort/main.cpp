#include "Student.h"
#define NUM_OF_STU 10000

int main() {

	int priority[6];
	cout << "Please input numbers in [1,6] to set the priority:" << endl;
	for (int i = 0; i < 6; i++)
		cin >> priority[i];

	Student stu[NUM_OF_STU];
	
	// bucketSort starts with the lowest priority
	int current_sub = 5;
	// bucket sort 
	for (current_sub; current_sub >= 0; current_sub--)
		mergeSort(stu, NUM_OF_STU, priority[current_sub]);
	
	// merge sort with total
	mergeSort(stu, NUM_OF_STU, 0);

	cout << "TOTAL--"
		<< "--S1---" 
		<< "---S2---" 
		<< "---S3---" 
		<< "---S4---" 
		<< "---S5---"
		<< "---S6" << endl;

	// print the sorted result
	for (int i = NUM_OF_STU-1; i >= 0; i--)
		cout << stu[i];

	return 0;
}