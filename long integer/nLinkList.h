#pragma once
#include <cassert>
#include <iostream>
using namespace std;
class nLinkList {
	// �ӷ�����������Ϊ�����������������������͵ĺ���ʾ����Ļ���޷���ֵ��
	friend void add(const nLinkList&, const nLinkList&);
	// �Ƚ�������С������Ϊ������������������һ��������Ӧ���������ϴ󣬷���true�����򷵻�false��
	friend bool greater(const nLinkList &, const nLinkList&);
private:
	struct node {    // �����
		int number;  // ���ݲ���
		node *next = NULL; // ָ�벿��
		node() :next(NULL) {} // Ĭ�Ϲ��캯��
		node(const int &x, node *n = NULL) // ���ع��캯��
			:number(x), next(n) {}
		~node() {}   // Ĭ����������
	};

	node *head; // ָ�������ͷ���
	int currentLength; // ����ǰ����
	node *move(int i)const; // ���ص�i�����ĵ�ַ ƽ�����Ӷ�O(n)

public:
	// Ĭ�Ϲ��캯��������һ��ͷ���������Ϊ1�Ŀ�����
	nLinkList() { head = new node(1); currentLength = 0; }
	// ���ƹ��캯��
	nLinkList(const nLinkList &); 
	// ��������
	~nLinkList() { clear(); delete head; }
	// �������
	void clear(); // ���Ӷ�O(n)
	// ����������ȡ����ĳ������������뵱ǰ����
	void input();
	// �������i��λ�ò���Ԫ��Ϊx�Ľ�㡣
	void insert(int i, const int &x); // ƽ�����Ӷ�ȡ����move������O(n)
	// �������������������洢�ĳ���������ʾ����Ļ�� ����ÿ����㣬���Ӷ�O(n)
	void traverse()const;

};
#include "nLinkList_imp.h"
