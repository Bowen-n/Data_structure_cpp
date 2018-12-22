#pragma once
#include <cassert>
#include <iostream>
using namespace std;
class nLinkList {
	// 加法函数。输入为两个长整型链表，将两长整型的和显示到屏幕，无返回值。
	friend void add(const nLinkList&, const nLinkList&);
	// 比较两数大小。输入为两个长整型链表，若第一个参数对应长整型数较大，返回true，否则返回false。
	friend bool greater(const nLinkList &, const nLinkList&);
private:
	struct node {    // 结点类
		int number;  // 数据部分
		node *next = NULL; // 指针部分
		node() :next(NULL) {} // 默认构造函数
		node(const int &x, node *n = NULL) // 重载构造函数
			:number(x), next(n) {}
		~node() {}   // 默认析构函数
	};

	node *head; // 指向链表的头结点
	int currentLength; // 链表当前长度
	node *move(int i)const; // 返回第i个结点的地址 平均复杂度O(n)

public:
	// 默认构造函数。生成一个头结点数据域为1的空链表。
	nLinkList() { head = new node(1); currentLength = 0; }
	// 复制构造函数
	nLinkList(const nLinkList &); 
	// 析构函数
	~nLinkList() { clear(); delete head; }
	// 清空链表
	void clear(); // 复杂度O(n)
	// 按输入规则读取输入的长整型数并存入当前链表。
	void input();
	// 在链表第i个位置插入元素为x的结点。
	void insert(int i, const int &x); // 平均复杂度取决于move函数，O(n)
	// 遍历链表，将此链表所存储的长整型数显示于屏幕。 遍历每个结点，复杂度O(n)
	void traverse()const;

};
#include "nLinkList_imp.h"
