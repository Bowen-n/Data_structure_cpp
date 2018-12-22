#pragma once
#include "Stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

// λ����
class Position {
public:
	int row; int col; // ����
	int options[8]; // ��������Ƿ񻹿��Գ���

	Position() :row(0), col(0) 
	{ for (int i = 0; i < 8 && (options[i] = 1); i++); }

	Position(int _row, int _col) :row(_row), col(_col)
	{ for (int i = 0; i < 8 && (options[i] = 1); i++); }
	virtual~Position() {};
	void set_position(int _row, int _col) { row = _row; col = _col; }
	void reset_a() { for (int i = 0; i < 8 && (options[i] = 1); i++); }
};

