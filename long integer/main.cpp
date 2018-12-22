#include "nLinkList.h"

int main() {
	char command; // 输入命令
	bool flag = true;
	do {
		cout << "Please input two integers:" << endl; // 输入提示
		nLinkList list1; list1.input(); // 输入长整数
		nLinkList list2; list2.input(); // 输入长整数
		add(list1, list2); // 相加
		cout << "Continue?( y or n )"; cin >> command; // 是否继续
		flag = (command == 'y') ? true : false;
	} while (flag);
	return 0;
}