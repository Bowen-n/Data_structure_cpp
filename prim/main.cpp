#include <iostream>
#include "adjListGraph.h"
using namespace std;


void test() {
	char vertex[8] = { 'a','b','c','d','e','f','g','h' };

	adjListGraph<char, int> graph(8, vertex);

	graph.insert('a', 'b', 4);
	graph.insert('a', 'c', 3);
	graph.insert('b', 'c', 5);
	graph.insert('b', 'd', 5);
	graph.insert('b', 'e', 9);
	graph.insert('c', 'd', 5);
	graph.insert('c', 'h', 5);
	graph.insert('d', 'e', 7);
	graph.insert('d', 'f', 6);
	graph.insert('d', 'g', 5);
	graph.insert('d', 'h', 4);
	graph.insert('e', 'f', 3);
	graph.insert('f', 'g', 2);
	graph.insert('g', 'h', 6);

	cout << "Please input the start node(0-7):";
	int startnode; cin >> startnode;
	while (startnode < 0 || startnode >7) {
		cout << "Error!Please try again." << endl;
		cin >> startnode;
	}

	graph.prim(100, startnode);
}

void random() {
	cout << "Please input the number of vertex(<=30):";
	int ver; cin >> ver;
	while (ver > 30) {
		cout << "Error!Please try again." << endl;
		cin >> ver;
	}

	int *vertex = new int[ver];
	assert(vertex != NULL);

	for (int i = 1; i <= ver; i++)
		vertex[i-1] = i;

	adjListGraph<int, int> graph(ver, vertex);

	// 1 2 3  (1,2) (1,3) (2,3) ver = 3
	int seed = 0;
	for (int i = 1; i <= ver - 1; i++)
		for (int j = i + 1; j <= ver; j++) {
			srand(seed++);
			graph.insert(i, j, rand() % 100);
		}


	cout << "Please input the start node(0-" << ver-1 << "):";
	int startnode; cin >> startnode;
	while (startnode<0 || startnode>ver-1) {
		cout << "Error!Please try again." << endl;
		cin >> startnode;
	}

	graph.prim(100, startnode);
}


int main() {

	cout << "(1)Generate weight randomly;" << endl;
	cout << "(2)Generate test data." << endl;
	cout << "Please input 1 or 2:" << endl;
	int select; cin >> select;
	while (select != 1 && select != 2) {
		cout << "Error! Please try again." << endl;
		cin >> select;
	}
	if (select == 2)
		test();
	else
		random();

	return 0;
}
