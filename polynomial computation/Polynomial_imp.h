#pragma once

// ���캯��
Polynomial::Polynomial()
	:head(new Node), currentLength(0) {}

// ��������
Polynomial::~Polynomial() {
	clear(); delete head;
}

// �������Ϊ���λ��i
// ���ص�i�����ĵ�ַ
Polynomial::Node *Polynomial::move(int i)const {
	Node *p = head;
	while (i-- >= 0 && (p = p->next));
	return p;
}

// �������
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

// ����Ԫ��
// �������Ϊ����λ��i������ĵ���ʽϵ��coff_��ָ��exp_
void Polynomial::insert(int i,
	const double coff_, const int exp_) {
	Node *pos = move(i - 1);
	pos->next = new Node(coff_, exp_, pos->next);
	++currentLength;
}

// ����exp_
// �������Ϊ�����ָ��
// �������д���ָ��Ϊexp_��Ԫ�أ����ظ�Ԫ��λ�ã�
// �������в�����ָ��Ϊexp_��Ԫ�أ�����-1��
int Polynomial::exist_same_exp(int exp_) {
	Node *p = head->next; int pos = 0;
	while (p != NULL) {
		if (exp_ == p->exp)
			return pos;
		p = p->next; ++pos;
	}
	return -1;
}

// ����Ԫ��λ�� 
// �������Ϊ�轻��������Ԫ�ص�λ�ã�Ĭ��i<j
void Polynomial::swap(int i, int j) {
	// i��j����
	if (j - i == 1) {
		Node *i_prev = move(i - 1);
		Node *i_ = i_prev->next;
		Node *j_succ = i_prev->next->next->next;
		i_prev->next = i_prev->next->next;
		i_->next = j_succ;
		i_prev->next->next = i_;
	}
	// i��j������
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

// ��ָ����������ð������
void Polynomial::sort() {
	// �����Ϊ0��1����������
	if (currentLength == 0 || currentLength == 1)
		return;

	bool flag = false; // �ж�ð�ݹ����Ƿ��н���
	int end_bubble = currentLength; // ���ð����ֹλ��

	while (!flag) {
		flag = true;
		// ��¼���λ��
		int i = 0, j = 1;
		Node *p = head->next; Node *q = p->next;
		while (j < end_bubble) {	// һ��
			if (p->exp > q->exp){ // ָ����ķź���
				swap(i, j);
				flag = false;
				p = q; q = p->next; // �ｻ��p,q
			}
			++i; p = p->next;
			++j; q = q->next;
		}
		--end_bubble;
	}
}

// ���루���������ʽ����
void Polynomial::input() {
	int num; cin >> num; // ����ʽ����
	double coff_;int exp_; // ��ȡϵ����ָ��
	for (int i = 0; i < num; i++) {
		cin >> coff_; cin >> exp_;
		// ���Ҹ�ָ���Ƿ����������Ѿ�����
		int tmp = exist_same_exp(exp_);
		// ���Ѿ����ڣ���ϵ�����뼴�ɡ�
		if (tmp != -1)
			move(tmp)->coff += coff_;
		// �������ڣ�������Ԫ�ء�
		else
			insert(0, coff_, exp_);
	}
}

// ���������������ʽ�����
void Polynomial::traverse()const {
	cout << "(";
	if (currentLength == 0)
		cout << "0";
	for (int i = currentLength - 1; i >= 0; i--) {
		Node *tmp = move(i);
		// ϵ��Ϊ���Ҳ��ǵ�һλ��������Ӻţ������Դ����ţ�
		if (i != currentLength - 1 && tmp->coff > 0)
			cout << "+";
		// ָ��Ϊ0�����ϵ������
		if (tmp->exp == 0) {
			cout << tmp->coff;
			continue;
		}
		else {
			// ���ϵ����-1�����������x
			if (tmp->coff == -1)
				cout << "-x";
			// ���ϵ������1�����ϵ����x
			else if (tmp->coff != 1)
				cout << tmp->coff << "x";
			// ϵ����1
			else
				cout << "x";
			// ָ����Ϊ1�����^��ָ��
			if (tmp->exp != 1) {
				cout << "^";
				// ָ��Ϊ�����������
				if (tmp->exp < 0)
					cout << "(" << tmp->exp << ")";
				else
					cout << tmp->exp;
			} // if
		} // else
	} // for
	cout << ")";
}

// ����ʽ���
// �������Ϊ��������ʽ���������
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
		else { // ָ����ͬ
			if (p->coff + q->coff != 0)
				insert(currentLength, p->coff + q->coff, p->exp);
			q = q->next; p = p->next;
		}
	}
	// ����δ��������
	Node *tmp = (p == NULL) ? q : p;
	while (tmp != NULL) {
		insert(currentLength, tmp->coff, tmp->exp);
		tmp = tmp->next;
	}
}


// ����ʽ���
// �������Ϊ��������ʽ���������
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
		else { // ָ����ͬ
			if (p->coff - q->coff != 0)
				insert(currentLength, p->coff - q->coff, p->exp);
			p = p->next; q = q->next;
		}
	}

	// ����δ��������
	Node *tmp = (p == NULL) ? q : p;
	while (tmp != NULL) {
		insert(currentLength,
			(tmp == p) ? tmp->coff : -tmp->coff,
			tmp->exp);
		tmp = tmp->next;
	}
}