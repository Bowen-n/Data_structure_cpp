#pragma once
#include "Position.h"

// ��ʾ��̤������
class Demo {
private:
	int board[8][8] = { 0 }; // ����
	Position current_pos; // ��ǰλ��
	Stack<Position> *backtrace; // ����ջ
	Position jump[8]; // ��������

	// �ж�����Ϸ���
	bool valid(int, int);
	// ������һ���м�������
	int count_next_jump(int, int);
public:
	Demo() {};
	Demo(int, int);
	virtual~Demo() { delete backtrace; backtrace == NULL; }
	// Ѱ����Ծ·��
	void find_path();
};

#include "Demo_imp.h"