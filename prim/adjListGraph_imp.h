#pragma once

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>
::adjListGraph(int vSize, const TypeOfVer d[]) {
	Vers = vSize;
	Edges = 0;

	verList = new verNode[vSize];
	assert(verList != NULL);
	for (int i = 0; i < Vers; i++)verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
	int u = find(x), v = find(y);
	verList[u].head = new edgeNode(v, w, verList[u].head);
	assert(verList[u].head != NULL);
	verList[v].head = new edgeNode(u, w, verList[v].head);
	assert(verList[v].head != NULL);

	++Edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::remove(TypeOfVer x, TypeOfVer y) {
	int u = find(x), v = find(y);
	edgeNode *p = verList[u].head, *q;

	if (p == NULL)return;
	if (p->end == v) {
		verList[u].head = p->next;
		delete p;
		--Edges;
		return;
	}

	while (p->next != NULL && p->next->end != v)p = p->next;
	if (p->next != NULL) {
		q = p->next;
		p->next = q->next;
		delete q;
		--Edges;
	}
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>
::exist(TypeOfVer x, TypeOfVer y)const {
	int u = find(x), v = find(y);
	edgeNode *p = verList[u].head;

	while (p != NULL && p->end != v)p = p->next;
	if (p == NULL)return false;
	else return true;
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
	edgeNode *p;

	for(int i=0;i<Vers;i++)
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p->next;
			delete p;
		}

	delete[]verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::prim(TypeOfEdge noEdge, const int startnode)const {
	bool *flag = new bool[Vers];
	assert(flag != NULL);
	TypeOfEdge *lowCost = new TypeOfEdge[Vers];
	assert(lowCost != NULL);
	int *startNode = new int[Vers];
	assert(startNode != NULL);

	edgeNode *p;
	TypeOfEdge min;

	for (int i = 0; i < Vers; i++) { // initialize
		flag[i] = false;
		lowCost[i] = noEdge;
	}

	cout << endl << "Edge" << setw(11) << "Weight" << endl;
	int start = startnode;
	for (int i = 1; i < Vers; i++) {
		for (p = verList[start].head; p != NULL; p = p->next) // check start's edge
			// update distance
			if (!flag[p->end] && (lowCost[p->end] > p->weight)) {
				lowCost[p->end] = p->weight;
				startNode[p->end] = start;
			}
		flag[start] = true;   // start --> U
		min = noEdge;
		for (int j = 0; j < Vers; j++) // find the least edge
			if (lowCost[j] < min) {
				min = lowCost[j];
				start = j;
			}

		cout <<"(" << verList[startNode[start]].ver << "," << verList[start].ver << ")" << setw(8);
		cout << min << endl;
		lowCost[start] = noEdge;
	}

	delete[]flag;
	delete[]startNode;
	delete[]lowCost;
}