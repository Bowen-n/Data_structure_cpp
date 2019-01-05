#pragma once
#include "Graph.h"
#include "linkQueue.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph :public Graph<TypeOfVer, TypeOfEdge> {

private:
	// node for edge in the linked list
	struct edgeNode {
		int end;
		TypeOfEdge weight;
		edgeNode *next;
		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
			:end(e), weight(w), next(n) {}
	};
	// node for verex
	struct verNode {
		TypeOfVer ver;
		int credit;
		// the head of the linked-list
		edgeNode *head;
		verNode(const int c = 0, edgeNode *h = NULL)
			:credit(c), head(h) {}
	};

	verNode *verList;
	int t_sems;
	int cre_max;
	int find(TypeOfVer v)const {
		for (int i = 0; i < Vers; i++)
			if (verList[i].ver == v)return i;
	}

	void dfs(int, bool visited[])const;
public:
	adjListGraph(int vSize, int semester, int credit, const int c[], const TypeOfVer d[]);
	void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
	void remove(TypeOfVer x, TypeOfVer y);
	bool exist(TypeOfVer x, TypeOfVer y)const;
	void topSort()const;

	void show_graph()const;
	~adjListGraph();

	void dfs()const;
	void bfs()const;
};

// implemented in
