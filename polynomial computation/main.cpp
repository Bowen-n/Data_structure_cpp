#include "Polynomial.h"
int main() {
	// opΪ�Ӽ�������commandΪ�Ƿ����
	char op; char command = 'y';

	while (command=='y') {
		Polynomial n1; Polynomial n2; 
		Polynomial result;
		cout << "Please input the first polynomial:" << endl;
		n1.input(); n1.sort(); // �������������
		cout << "Please input the second polynomial:" << endl;
		n2.input(); n2.sort(); // �������������
		cout << "Please input the operation ( + or - ):";
		cin >> op;
		// ����ʽ���
		if (op == '+') {
			result.add(n1, n2);
			n1.traverse(); cout << "+"; n2.traverse(); cout << "="; 
			result.traverse(); cout << endl << endl;
		}
		// ����ʽ���
		if (op == '-') {
			result.sub(n1, n2);
			n1.traverse(); cout << "-"; n2.traverse(); cout << "=";
			result.traverse(); cout << endl << endl;
		}
		// �Ƿ����
		cout << "Continue? ( y or n ):"; cin >> command;
	}

	return 0;
}