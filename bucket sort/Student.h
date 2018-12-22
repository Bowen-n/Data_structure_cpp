#pragma once
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#define WIDTH 8
using namespace std;

class Student {
	friend ostream& operator<<(ostream &, Student &);
private:
	static unsigned int order_;
public:
	// total scores
	int total;
	// six scores
	int s1; int s2; int s3; int s4; int s5; int s6;
	// order
	int order;

	Student();
	~Student() {};
};

unsigned int Student::order_ = 0;

Student::Student() {
	srand(order_);
	s1 = rand() % 101; s2 = rand() % 101;
	s3 = rand() % 101; s4 = rand() % 101;
	s5 = rand() % 101; s6 = rand() % 101;
	total = s1 + s2 + s3 + s4 + s5 + s6;
	order = ++order_;
}

ostream&operator<<(ostream &out, Student &obj) {
	out << obj.total << setw(WIDTH)
		<< obj.s1 << setw(WIDTH)
		<< obj.s2 << setw(WIDTH)
		<< obj.s3 << setw(WIDTH)
		<< obj.s4 << setw(WIDTH)
		<< obj.s5 << setw(WIDTH)
		<< obj.s6 << endl;
	return out;
}

#include "MergeSort.h"
