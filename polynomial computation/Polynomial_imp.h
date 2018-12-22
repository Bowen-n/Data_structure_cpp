#pragma once

// 构造函数
Polynomial::Polynomial()
	:head(new Node), currentLength(0) {}

// 析构函数
Polynomial::~Polynomial() {
	clear(); delete head;
}

// 输入参数为结点位置i
// 返回第i个结点的地址
Polynomial::Node *Polynomial::move(int i)const {
	Node *p = head;
	while (i-- >= 0 && (p = p->next));
	return p;
}

// 清除链表
void Polynomial::clear() {
	Node *p = head->next, *q;
	head->next = NULL;
	while (p != NULL) {
		q = p->next;
		delete p;
		p = q;
	}
	currentLength = 0;
}

// 插入元素
// 输入参数为插入位置i，插入的单项式系数coff_，指数exp_
void Polynomial::insert(int i,
	const double coff_, const int exp_) {
	Node *pos = move(i - 1);
	pos->next = new Node(coff_, exp_, pos->next);
	++currentLength;
}

// 查找exp_
// 输入参数为需检查的指数
// 若链表中存在指数为exp_的元素，返回该元素位置；
// 若链表中不存在指数为exp_的元素，返回-1。
int Polynomial::exist_same_exp(int exp_) {
	Node *p = head->next; int pos = 0;
	while (p != NULL) {
		if (exp_ == p->exp)
			return pos;
		p = p->next; ++pos;
	}
	return -1;
}

// 交换元素位置 
// 输入参数为需交换的两个元素的位置，默认i<j
void Polynomial::swap(int i, int j) {
	// i与j相邻
	if (j - i == 1) {
		Node *i_prev = move(i - 1);
		Node *i_ = i_prev->next;
		Node *j_succ = i_prev->next->next->next;
		i_prev->next = i_prev->next->next;
		i_->next = j_succ;
		i_prev->next->next = i_;
	}
	// i与j不相邻
	else {
		Node *i_prev = move(i - 1);
		Node *j_prev = move(j - 1);
		Node *tmp = i_prev->next->next;
		i_prev->next->next = j_prev->next->next;
		j_prev->next->next = tmp;
		tmp = i_prev->next;
		i_prev->next = j_prev->next;
		j_prev->next = tmp;
	}
}

// 按指数升序排序（冒泡排序）
void Polynomial::sort() {
	// 如果表长为0或1，无需排序
	if (currentLength == 0 || currentLength == 1)
		return;

	bool flag = false; // 判断冒泡过程是否有交换
	int end_bubble = currentLength; // 存放冒泡终止位置

	while (!flag) {
		flag = true;
		// 记录检查位置
		int i = 0, j = 1;
		Node *p = head->next; Node *q = p->next;
		while (j < end_bubble) {	// 一轮
			if (p->exp > q->exp){ // 指数大的放后面
				swap(i, j);
				flag = false;
				p = q; q = p->next; // ★交换p,q
			}
			++i; p = p->next;
			++j; q = q->next;
		}
		--end_bubble;
	}
}

// 输入（按照输入格式处理）
void Polynomial::input() {
	int num; cin >> num; // 多项式项数
	double coff_;int exp_; // 读取系数与指数
	for (int i = 0; i < num; i++) {
		cin >> coff_; cin >> exp_;
		// 查找该指数是否在链表中已经存在
		int tmp = exist_same_exp(exp_);
		// 若已经存在，将系数加入即可。
		if (tmp != -1)
			move(tmp)->coff += coff_;
		// 若不存在，插入新元素。
		else
			insert(0, coff_, exp_);
	}
}

// 遍历（按照输出格式输出）
void Polynomial::traverse()const {
	cout << "(";
	if (currentLength == 0)
		cout << "0";
	for (int i = currentLength - 1; i >= 0; i--) {
		Node *tmp = move(i);
		// 系数为正且不是第一位，需输出加号（负数自带减号）
		if (i != currentLength - 1 && tmp->coff > 0)
			cout << "+";
		// 指数为0，输出系数即可
		if (tmp->exp == 0) {
			cout << tmp->coff;
			continue;
		}
		else {
			// 如果系数是-1，输出负号与x
			if (tmp->coff == -1)
				cout << "-x";
			// 如果系数不是1，输出系数与x
			else if (tmp->coff != 1)
				cout << tmp->coff << "x";
			// 系数是1
			else
				cout << "x";
			// 指数不为1，输出^与指数
			if (tmp->exp != 1) {
				cout << "^";
				// 指数为负输出加括号
				if (tmp->exp < 0)
					cout << "(" << tmp->exp << ")";
				else
					cout << tmp->exp;
			} // if
		} // else
	} // for
	cout << ")";
}

// 多项式相加
// 输入参数为两个多项式链表的引用
void Polynomial::add(const Polynomial &add1,
	const Polynomial &add2) {
	Node *p = add1.head->next;
	Node *q = add2.head->next;
	while (p != NULL && q != NULL) {
		if (p->exp < q->exp) {
			insert(currentLength, p->coff, p->exp);
			p = p->next;
		}
		else if (p->exp > q->exp) {
			insert(currentLength, q->coff, q->exp);
			q = q->next;
		}
		else { // 指数相同
			if (p->coff + q->coff != 0)
				insert(currentLength, p->coff + q->coff, p->exp);
			q = q->next; p = p->next;
		}
	}
	// 处理未结束的项
	Node *tmp = (p == NULL) ? q : p;
	while (tmp != NULL) {
		insert(currentLength, tmp->coff, tmp->exp);
		tmp = tmp->next;
	}
}


// 多项式相减
// 输入参数为两个多项式链表的引用
void Polynomial::sub(const Polynomial &sub1,
	const Polynomial &sub2) {
	Node *p = sub1.head->next;
	Node *q = sub2.head->next;

	while (p != NULL && q != NULL) {
		if (p->exp < q->exp) {
			insert(currentLength, p->coff, p->exp);
			p = p->next;
		}
		else if (p->exp > q->exp) {
			insert(currentLength, -(q->coff), q->exp);
			q = q->next;
		}
		else { // 指数相同
			if (p->coff - q->coff != 0)
				insert(currentLength, p->coff - q->coff, p->exp);
			p = p->next; q = q->next;
		}
	}

	// 处理未结束的项
	Node *tmp = (p == NULL) ? q : p;
	while (tmp != NULL) {
		insert(currentLength,
			(tmp == p) ? tmp->coff : -tmp->coff,
			tmp->exp);
		tmp = tmp->next;
	}
}