#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

// 多项式链表类的定义
class Polynomial {
private:
	// 结点类
	class Node {
	public:
		double coff; // 存储系数
		int exp;  // 存储指数
		Node *next;

		Node() :next(NULL) {} // 默认构造函数
		Node(double coff_, int exp_, Node *p = NULL)
			:coff(coff_), exp(exp_), next(p) {}
	};

	Node *head; // 头指针
	int currentLength; // 长度

	// 返回第i个结点的地址
	// 平均复杂度O(n)
	Node *move(int i)const;
public:	
	// 构造函数
	Polynomial();
	// 析构函数
	virtual ~Polynomial();

	// 链表长度
	// 复杂度O(1)
	int length()const { return currentLength; }
	// 清除链表
	// 复杂度O(n)
	void clear();
	// 插入元素
	// 复杂度取决于move，平均复杂度O(n)
	void insert(int i, const double coff_, const int exp_);
	// 是否存在与输入相同的指数
	// 与exp_值有关，复杂度最好为O(1)，最坏为O(n)
	int exist_same_exp(int exp_);

	// 交换两个结点
	// 复杂度取决于move，平均复杂度O(n)
	void swap(int, int);
	// 按指数排序
	// 冒泡排序复杂度为O(n^2),但其中交换操作平均复杂度为O(n),
	// 故排序平均复杂度为O(n^3)。
	void sort();
	
	// 输入
	// 最好复杂度O(n),最坏复杂度O(n^2)
	void input();
	// 遍历
	// 复杂度O(n)
	void traverse()const;
	
	// 多项式相加
	// 复杂度O(n^2)
	void add(const Polynomial &add1, const Polynomial &add2);
	// 多项式相减
	// 复杂度O(n^2)
	void sub(const Polynomial &sub1, const Polynomial &sub2);
};

#include "Polynomial_imp.h"