#include "Polynomial.h"
int main() {
	// op为加减操作，command为是否继续
	char op; char command = 'y';

	while (command=='y') {
		Polynomial n1; Polynomial n2; 
		Polynomial result;
		cout << "Please input the first polynomial:" << endl;
		n1.input(); n1.sort(); // 输入后立即排序
		cout << "Please input the second polynomial:" << endl;
		n2.input(); n2.sort(); // 输入后立即排序
		cout << "Please input the operation ( + or - ):";
		cin >> op;
		// 多项式相加
		if (op == '+') {
			result.add(n1, n2);
			n1.traverse(); cout << "+"; n2.traverse(); cout << "="; 
			result.traverse(); cout << endl << endl;
		}
		// 多项式相减
		if (op == '-') {
			result.sub(n1, n2);
			n1.traverse(); cout << "-"; n2.traverse(); cout << "=";
			result.traverse(); cout << endl << endl;
		}
		// 是否继续
		cout << "Continue? ( y or n ):"; cin >> command;
	}

	return 0;
}