#pragma once

// ����ջ��
template <class elemType> class Stack {
private:
	int top; __int64 maxTop; // ջ�����������
	elemType *stack;

public:
	Stack(int maxSize = 64)
		:maxTop(maxSize - 1), stack(new elemType[maxSize]), top(-1) {}
	~Stack() { delete[]stack; }
	// ��ջ
	void push(const elemType &x) { stack[++top] = x; }
	// ��ջ
	void pop(elemType &x) { x = stack[top--]; }
};