#pragma once

template<class elemType>
linkQueue<elemType>::linkQueue()
	:front(NULL), rear(NULL) {}

template<class elemType>
linkQueue<elemType>::~linkQueue() {
	node *tmp;
	while (front != NULL) {
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class elemType>
bool linkQueue<elemType>::isEmpty()const {
	return front == NULL;
}

template<class elemType>
elemType linkQueue<elemType>::getHead()const {
	return front->data;
}

template<class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
	if (rear == NULL)
		front = rear = new node(x);
	else
		rear = rear->next = new node(x);
}

template<class elemType>
elemType linkQueue<elemType>::deQueue() {
	node *tmp = front;
	elemType value = front->data;
	front = front->next;

	if (front == NULL)rear = NULL;
	delete tmp;
	return value;
}

template<class elemType>
bool linkQueue<elemType>::isinQueue(const elemType x)const {
	if (isEmpty())
		return false;

	node *tmp = front;
	while (true) {
		if (tmp->data == x)
			return true;
		else {
			if (tmp == rear)
				return false;
			tmp = tmp->next;
		}
	}

}
