#pragma once

// 复制构造函数
nLinkList::nLinkList(const nLinkList &obj) {
	head = new node(obj.head->number); // 复制头结点数据域
	for (int i = 0; i < obj.currentLength; i++) // 复制每个结点数据域
		this->insert(i, obj.move(i)->number);
	currentLength = obj.currentLength; // 复制链表长度
}

// 参数i为所需访问的结点位置，返回值为第i个结点的地址
nLinkList::node *nLinkList::move(int i)const {
	node *p = head;
	while (i-- >= 0)p = p->next;
	return p;
}

// 清空链表 复杂度O(n)
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

// 按输入规则读取输入的长整型数并存入当前链表。
void nLinkList::input() {
	nLinkList tmp; // 创建临时链表用于读取每一位数字
	char temp; cin >> temp; // 读取第一位输入的字符
	if (temp == '-') // 如果为负号
		head->number = -1; // 头结点数据域变为-1
	else  
		tmp.insert(tmp.currentLength, temp - '0'); // 否则存入临时链表
	while (true) {
		cin >> temp; 
		if (temp >= '0'&& temp <= '9') // 如果读入为0-9，存入临时链表
			tmp.insert(tmp.currentLength, temp - '0');
		if (temp == ',' || temp== ';') { // 如果读入字符为逗号或分号
			switch (tmp.currentLength) { // 将临时链表中的数据转化为不大于9999的非负整数并存入链表
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
			tmp.clear(); // 清空临时链表
			if (temp == ',') // 如果读入字符为逗号，继续下个循环
				continue;
			else // 读入为分号，退出循环
				break;
		}
	}
}

// 插入函数
// 第一个参数为欲插入的位置，第二个参数为插入的结点的数据域
void nLinkList::insert(int i, const int &x) {
	node *pos = move(i - 1);
	pos->next = new node(x, pos->next);
	++currentLength;
}

// 遍历 将此链表所存储的长整型数显示于屏幕
void nLinkList::traverse()const {
	node *p;
	if (head->number == -1) cout << "-";
	bool flag = false; // 最高位是否为0
	for (int i = currentLength - 1; i >= 0; i--) {
		p = move(i);
		if (i == currentLength - 1 && p->number == 0 && i != 0) {
			flag = true; continue; // 最高位是0
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
			int leng = 0; // 位数
			while (tmp) {
				tmp /= 10;
				leng++;
			}
			if (!leng)leng++; // 0也是一位数
			for (int j = 0; j < 4 - leng; j++)
				cout << "0";
		}
		cout << p->number;
		if (i != 0)cout << ",";
	}
	cout << endl;
}

// 加法函数。此函数将两个长整数相加并将结果显示与屏幕
// 输入参数为两个长整型链表的引用，无返回值
void add(const nLinkList &add1, const nLinkList &add2) {
	nLinkList bigger = greater(add1, add2) ? add1 : add2; // 存放绝对值较大者
	nLinkList smaller = greater(add1, add2) ? add2 : add1; // 存放绝对值较小者
	nLinkList result; // 存放结果	
	if (add1.head->number == add2.head->number) { // 同号
		result.head->number = add1.head->number;
		int i, carry = 0; // 进位
		for (i = 0; i < smaller.currentLength; i++) { // 两个加数对应位都存在
			int temp_result = add1.move(i)->number
				+ add2.move(i)->number + carry;
			result.insert(result.currentLength, temp_result % 10000);
			carry = temp_result / 10000;
		}
		while (i < bigger.currentLength) { // 对多余位的处理
			int temp_result = bigger.move(i)->number + carry;
			result.insert(result.currentLength, temp_result % 10000);
			carry = temp_result / 10000; i++;
		}
		if (carry)
			result.insert(result.currentLength, carry);
	}
	else { // 异号
		result.head->number = bigger.head->number; // 结果符号为绝对值较大数的符号
		int i, minus = 0; // 借位
		for (i = 0; i < smaller.currentLength; i++) { // 对应位都存在
			int temp_result = bigger.move(i)->number
				- smaller.move(i)->number - minus;
			if (temp_result < 0)
				temp_result += 10000, minus = 1;
			else minus = 0;
			result.insert(result.currentLength, temp_result);
		}
		while (i < bigger.currentLength) { // 对多余位的处理
			int temp_result = bigger.move(i)->number - minus;
			if (temp_result < 0)
				temp_result += 10000, minus = 1;
			else minus = 0; i++;
			result.insert(result.currentLength, temp_result);
		}
	}
	result.traverse(); // 遍历结果
}


// 比较两数绝对值的大小
// 输入为两个长整型链表引用，若n1>n2，返回true，否则返回else
bool greater(const nLinkList &n1, const nLinkList &n2) {
	if (n1.currentLength > n2.currentLength) // 先比较长度，长度大的可以直接返回
		return true;
	else if (n1.currentLength < n2.currentLength)
		return false;
	for (int i = 0; i < n1.currentLength; i++) { // 若长度相同
		if (n1.move(i)->number > n2.move(i)->number) // 逐位比较
			return true;
		else if (n1.move(i)->number < n2.move(i)->number)
			return false;
	}
	return true;
}