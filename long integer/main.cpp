#include "nLinkList.h"

int main() {
	char command; // ��������
	bool flag = true;
	do {
		cout << "Please input two integers:" << endl; // ������ʾ
		nLinkList list1; list1.input(); // ���볤����
		nLinkList list2; list2.input(); // ���볤����
		add(list1, list2); // ���
		cout << "Continue?( y or n )"; cin >> command; // �Ƿ����
		flag = (command == 'y') ? true : false;
	} while (flag);
	return 0;
}