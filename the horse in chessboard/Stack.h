#pragma once

// 泛型栈类
template <class elemType> class Stack {
private:
	int top; __int64 maxTop; // 栈顶，最大容量
	elemType *stack;

public:
	Stack(int maxSize = 64)
		:maxTop(maxSize - 1), stack(new elemType[maxSize]), top(-1) {}
	~Stack() { delete[]stack; }
	// 入栈
	void push(const elemType &x) { stack[++top] = x; }
	// 出栈
	void pop(elemType &x) { x = stack[top--]; }
};