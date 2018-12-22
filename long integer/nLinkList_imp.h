#pragma once

// ���ƹ��캯��
nLinkList::nLinkList(const nLinkList &obj) {
	head = new node(obj.head->number); // ����ͷ���������
	for (int i = 0; i < obj.currentLength; i++) // ����ÿ�����������
		this->insert(i, obj.move(i)->number);
	currentLength = obj.currentLength; // ����������
}

// ����iΪ������ʵĽ��λ�ã�����ֵΪ��i�����ĵ�ַ
nLinkList::node *nLinkList::move(int i)const {
	node *p = head;
	while (i-- >= 0)p = p->next;
	return p;
}

// ������� ���Ӷ�O(n)
void nLinkList::clear() {
	node *p = head->next, *q;
	head->next = NULL;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	currentLength = 0;
}

// ����������ȡ����ĳ������������뵱ǰ����
void nLinkList::input() {
	nLinkList tmp; // ������ʱ�������ڶ�ȡÿһλ����
	char temp; cin >> temp; // ��ȡ��һλ������ַ�
	if (temp == '-') // ���Ϊ����
		head->number = -1; // ͷ����������Ϊ-1
	else  
		tmp.insert(tmp.currentLength, temp - '0'); // ���������ʱ����
	while (true) {
		cin >> temp; 
		if (temp >= '0'&& temp <= '9') // �������Ϊ0-9��������ʱ����
			tmp.insert(tmp.currentLength, temp - '0');
		if (temp == ',' || temp== ';') { // ��������ַ�Ϊ���Ż�ֺ�
			switch (tmp.currentLength) { // ����ʱ�����е�����ת��Ϊ������9999�ķǸ���������������
			case 1:insert(0, tmp.move(0)->number); break;
			case 2:insert(0, tmp.move(0)->number * 10 
				+ tmp.move(1)->number); break;
			case 3:insert(0, tmp.move(0)->number * 100 
				+ tmp.move(1)->number * 10 
				+ tmp.move(2)->number); break;
			case 4:insert(0, tmp.move(0)->number * 1000
				+ tmp.move(1)->number * 100
				+ tmp.move(2)->number * 10
				+ tmp.move(3)->number); break;
			default:break;
			}
			tmp.clear(); // �����ʱ����
			if (temp == ',') // ��������ַ�Ϊ���ţ������¸�ѭ��
				continue;
			else // ����Ϊ�ֺţ��˳�ѭ��
				break;
		}
	}
}

// ���뺯��
// ��һ������Ϊ�������λ�ã��ڶ�������Ϊ����Ľ���������
void nLinkList::insert(int i, const int &x) {
	node *pos = move(i - 1);
	pos->next = new node(x, pos->next);
	++currentLength;
}

// ���� �����������洢�ĳ���������ʾ����Ļ
void nLinkList::traverse()const {
	node *p;
	if (head->number == -1) cout << "-";
	bool flag = false; // ���λ�Ƿ�Ϊ0
	for (int i = currentLength - 1; i >= 0; i--) {
		p = move(i);
		if (i == currentLength - 1 && p->number == 0 && i != 0) {
			flag = true; continue; // ���λ��0
		}
		if (flag && i!=currentLength-1) {
			int tmp = p->number;
			if (tmp != 0 && i!=0)flag = false;
			else {
				if (i == 0)cout << tmp;
				continue;
			}
		}
		if (!flag && i!=currentLength-1) {
			int tmp = p->number;
			int leng = 0; // λ��
			while (tmp) {
				tmp /= 10;
				leng++;
			}
			if (!leng)leng++; // 0Ҳ��һλ��
			for (int j = 0; j < 4 - leng; j++)
				cout << "0";
		}
		cout << p->number;
		if (i != 0)cout << ",";
	}
	cout << endl;
}

// �ӷ��������˺�����������������Ӳ��������ʾ����Ļ
// �������Ϊ������������������ã��޷���ֵ
void add(const nLinkList &add1, const nLinkList &add2) {
	nLinkList bigger = greater(add1, add2) ? add1 : add2; // ��ž���ֵ�ϴ���
	nLinkList smaller = greater(add1, add2) ? add2 : add1; // ��ž���ֵ��С��
	nLinkList result; // ��Ž��	
	if (add1.head->number == add2.head->number) { // ͬ��
		result.head->number = add1.head->number;
		int i, carry = 0; // ��λ
		for (i = 0; i < smaller.currentLength; i++) { // ����������Ӧλ������
			int temp_result = add1.move(i)->number
				+ add2.move(i)->number + carry;
			result.insert(result.currentLength, temp_result % 10000);
			carry = temp_result / 10000;
		}
		while (i < bigger.currentLength) { // �Զ���λ�Ĵ���
			int temp_result = bigger.move(i)->number + carry;
			result.insert(result.currentLength, temp_result % 10000);
			carry = temp_result / 10000; i++;
		}
		if (carry)
			result.insert(result.currentLength, carry);
	}
	else { // ���
		result.head->number = bigger.head->number; // �������Ϊ����ֵ�ϴ����ķ���
		int i, minus = 0; // ��λ
		for (i = 0; i < smaller.currentLength; i++) { // ��Ӧλ������
			int temp_result = bigger.move(i)->number
				- smaller.move(i)->number - minus;
			if (temp_result < 0)
				temp_result += 10000, minus = 1;
			else minus = 0;
			result.insert(result.currentLength, temp_result);
		}
		while (i < bigger.currentLength) { // �Զ���λ�Ĵ���
			int temp_result = bigger.move(i)->number - minus;
			if (temp_result < 0)
				temp_result += 10000, minus = 1;
			else minus = 0; i++;
			result.insert(result.currentLength, temp_result);
		}
	}
	result.traverse(); // �������
}


// �Ƚ���������ֵ�Ĵ�С
// ����Ϊ�����������������ã���n1>n2������true�����򷵻�else
bool greater(const nLinkList &n1, const nLinkList &n2) {
	if (n1.currentLength > n2.currentLength) // �ȱȽϳ��ȣ����ȴ�Ŀ���ֱ�ӷ���
		return true;
	else if (n1.currentLength < n2.currentLength)
		return false;
	for (int i = 0; i < n1.currentLength; i++) { // ��������ͬ
		if (n1.move(i)->number > n2.move(i)->number) // ��λ�Ƚ�
			return true;
		else if (n1.move(i)->number < n2.move(i)->number)
			return false;
	}
	return true;
}