#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

// ����ʽ������Ķ���
class Polynomial {
private:
	// �����
	class Node {
	public:
		double coff; // �洢ϵ��
		int exp;  // �洢ָ��
		Node *next;

		Node() :next(NULL) {} // Ĭ�Ϲ��캯��
		Node(double coff_, int exp_, Node *p = NULL)
			:coff(coff_), exp(exp_), next(p) {}
	};

	Node *head; // ͷָ��
	int currentLength; // ����

	// ���ص�i�����ĵ�ַ
	// ƽ�����Ӷ�O(n)
	Node *move(int i)const;
public:	
	// ���캯��
	Polynomial();
	// ��������
	virtual ~Polynomial();

	// ������
	// ���Ӷ�O(1)
	int length()const { return currentLength; }
	// �������
	// ���Ӷ�O(n)
	void clear();
	// ����Ԫ��
	// ���Ӷ�ȡ����move��ƽ�����Ӷ�O(n)
	void insert(int i, const double coff_, const int exp_);
	// �Ƿ������������ͬ��ָ��
	// ��exp_ֵ�йأ����Ӷ����ΪO(1)���ΪO(n)
	int exist_same_exp(int exp_);

	// �����������
	// ���Ӷ�ȡ����move��ƽ�����Ӷ�O(n)
	void swap(int, int);
	// ��ָ������
	// ð�������Ӷ�ΪO(n^2),�����н�������ƽ�����Ӷ�ΪO(n),
	// ������ƽ�����Ӷ�ΪO(n^3)��
	void sort();
	
	// ����
	// ��ø��Ӷ�O(n),����Ӷ�O(n^2)
	void input();
	// ����
	// ���Ӷ�O(n)
	void traverse()const;
	
	// ����ʽ���
	// ���Ӷ�O(n^2)
	void add(const Polynomial &add1, const Polynomial &add2);
	// ����ʽ���
	// ���Ӷ�O(n^2)
	void sub(const Polynomial &sub1, const Polynomial &sub2);
};

#include "Polynomial_imp.h"