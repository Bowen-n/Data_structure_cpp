#pragma once
#include "adjListGraph.h"

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>
::adjListGraph(int vSize, int semester, int credit
	, const int c[], const TypeOfVer d[])
	:t_sems(semester), cre_max(credit) {

	Vers = vSize;
	Edges = 0;
	verList = new verNode[vSize];
	assert(verList != NULL);
	for (int i = 0; i < Vers; i++) {
		verList[i].credit = c[i];
		verList[i].ver = d[i];
	}
}

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
	edgeNode *p;

	for (int i = 0; i < Vers; i++)
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p->next;
			delete p;
		}

	delete[]verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
	int u = find(x), v = find(y);

	verList[u].head = new edgeNode(v, w, verList[u].head);
	++Edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::remove(TypeOfVer x, TypeOfVer y) {
	int u = find(x), v = find(y);
	edgeNode *p = verList[u].head, *q;

	if (p == NULL)return;

	// the first node is the edge to be removed
	if (p->end == v) {
		verList[u].head = p->next;
		delete p;
		--Edges;
		return;
	}

	while (p->next != NULL && p->next->end != v) p = p->next;

	// find and delete edge
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

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::topSort()const {
	linkQueue<int> q;
	edgeNode *p;

	int current;

	// array of nodes' in degree
	int *inDegree = new int[Vers];

	// calculate the in-degree of every vertex
	// and store them in inDegree[]
	for (int i = 0; i<Vers; i++)

		inDegree[i] = 0;
	for (int i = 0; i < Vers; i++) {

		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end];
	}

	for (int i = 0; i < Vers; i++)
		if (inDegree[i] == 0)q.enQueue(i);

	cout << "Top sort:" << endl;
	while (!q.isEmpty()) {
		current = q.deQueue();
		cout << verList[current].ver << '\t';
		for (p = verList[current].head; p != NULL; p = p->next)
			if (--inDegree[p->end] == 0)
				q.enQueue(p->end);
	}
	cout << endl;

	delete[]inDegree;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::show_graph() const {
	for (int i = 0; i < Vers; i++) {

		edgeNode *p;
		cout << verList[i].ver;
		for (p = verList[i].head; p != NULL; p = p->next)
			cout << "->" << verList[p->end].ver;

		cout << endl;

	}
	return;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::dfs()const {
	bool *visited = new bool[Vers];

	for (int i = 0; i < Vers; i++)visited[i] = false;

	cout << "dfs:" << endl;

	for (int i = 0; i < Vers; i++) {
		if (visited[i] == true)continue;
		dfs(i, visited);
		cout << endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::dfs(int start, bool visited[])const {
	edgeNode *p = verList[start].head;

	cout << verList[start].ver << '\t';
	visited[start] = true;

	while (p != NULL) {
		if (visited[p->end] == false)
			dfs(p->end, visited);
		p = p->next;
	}

}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::bfs()const {
	bool *visited = new bool[Vers];
	int currentNode;
	linkQueue<int> q;
	edgeNode *p;

	for (int i = 0; i < Vers; i++)visited[i] = false;

	cout << "bfs:" << endl;

	for (int i = 0; i < Vers; i++) {
		if (visited[i] == true)continue;
		q.enQueue(i);

		while (!q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true)continue;
			cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;

			p = verList[currentNode].head;
			while (p != NULL) {
				if (visited[p->end] == false)q.enQueue(p->end);
				p = p->next;
			}// while
		}// while

		cout << endl;
	}// for
}