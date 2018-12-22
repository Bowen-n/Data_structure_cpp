#pragma once
#include "Position.h"

// 演示马踏棋盘类
class Demo {
private:
	int board[8][8] = { 0 }; // 棋盘
	Position current_pos; // 当前位置
	Stack<Position> *backtrace; // 回溯栈
	Position jump[8]; // 八种跳法

	// 判断坐标合法性
	bool valid(int, int);
	// 计算下一步有几种跳法
	int count_next_jump(int, int);
public:
	Demo() {};
	Demo(int, int);
	virtual~Demo() { delete backtrace; backtrace == NULL; }
	// 寻找跳跃路径
	void find_path();
};

#include "Demo_imp.h"