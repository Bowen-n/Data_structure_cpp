#pragma once

template <class TypeOfVer, class TypeOfEdge>
class Graph {
public:
	virtual void insert(TypeOfVer, TypeOfVer, TypeOfEdge) = 0;
	virtual void remove(TypeOfVer, TypeOfVer) = 0;
	virtual bool exist(TypeOfVer, TypeOfVer)const = 0;
	int numOfVer()const { return Vers; }
	int numOfEdge()const { return Edges; }
protected:
	int Vers, Edges;
};