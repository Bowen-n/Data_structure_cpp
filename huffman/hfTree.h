#pragma once
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAX_DOUBLE 1.79e308
using namespace std;

// huffman tree class
class hfTree {
private:
	// node in the huffman tree
	struct Node {
		char data; // calue
		double weight; // weight
		int parent, left, right;
	};

	char *v; // store characters
	double *w; // store weights
	Node *elem; // store huffman tree
	int length; // the scale of the huffman tree

	// recursion for treePrint
	void treePrint_recursion(int, string, ofstream&);
public:
	struct hfCode { // store encode result
		char data; // character
		string code; // code
	};

	// constructor
	hfTree() {};
	// set size, v, w
	void setSize_v_w(const int&);
	// get the size
	int getSize() { return length >> 1; }
	// initialize the huffman tree according to v and w
	void initialize();

	// get the code and store it into result[]
	void getCode(hfCode result[]);
	// encode the file in source(path)
	void encode(string source, const hfCode result[]);
	// decode the file in source(path)
	void decode(string source);
	// print the coding result
	void codePrint(string source);
	// print the huffman tree
	void treePrint();
	// encode the message in source(path)
	void encode_for_message(string source);
	// decode the data in source(path)
	void decode_for_message(string source);

	// show elem (for debugging)
	void showMemory();

	// destructor
	virtual~hfTree() { delete[]elem; delete[]v; delete[]w; }
};

#include "hfTree_imp.h"