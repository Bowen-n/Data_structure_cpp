#pragma once
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <iomanip>
#include "Graph.h"
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph :public Graph<TypeOfVer, TypeOfEdge> {
public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
	void remove(TypeOfVer x, TypeOfVer y);
	bool exist(TypeOfVer x, TypeOfVer y)const;
	~adjListGraph();

	// prim
	void prim(TypeOfEdge noEdge, const int startnode) const;

private:
	struct edgeNode {
		int end;
		TypeOfEdge weight;
		edgeNode *next;

		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
			:end(e), weight(w), next(n) {}
	};

	struct verNode {
		TypeOfVer ver;
		edgeNode *head;

		verNode(edgeNode *h = NULL) :head(h) {}
	};

	verNode *verList;
	int find(TypeOfVer v)const {
		for (int i = 0; i < Vers; i++)
			if (verList[i].ver == v)return i;
	}

};

// implementation
#include "adjListGraph_imp.h"