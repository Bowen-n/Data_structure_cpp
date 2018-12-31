#pragma once

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
::exist(TypeOfVer x, TypeOfVer y)const{
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
	for(int i=0;i<Vers;i++)

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
::build_plan_v1(const string file_name, bool &flag)const {

	string path = file_name + ".txt";
	ofstream file(path);

	file << "SEMESTER" << setw(10) << "CLASS_ID" << setw(10) << "CREDIT" << endl;

	linkQueue<int>q;
	edgeNode *p;

	// in_degree stores the in degree of every vertex
	int *in_degree = new int[Vers];
	for (int i = 0; i < Vers; i++)
		in_degree[i] = 0;

	// initialize in_degree
	for (int i = 0; i < Vers; i++)
		for (p = verList[i].head; p != NULL; p = p->next)
			++in_degree[p->end];

	// loop for semester
	for (int i = 1; i <= this->t_sems; i++) {

		int total_credit_ = 0;

		// check all courses that are available
		for (int j = 0; j < Vers; j++)
			if (in_degree[j] == 0 && !q.isinQueue(j))
				q.enQueue(j);


		bool if_no_class = true;
		while (!q.isEmpty()) {
			int course = q.getHead();
			total_credit_ += verList[course].credit;

			// can attend this course
			if (total_credit_ <= this->cre_max) {
				q.deQueue();
				file << setw(4) << i << setw(11);
				file << verList[course].ver << setw(10);
				file << verList[course].credit << endl;
				// update in-degree
				for (p = verList[course].head; p != NULL; p = p->next)
					--in_degree[p->end];

				in_degree[course] = -1;
				if_no_class = false;
			}

			else break;

		}// while

		if (!if_no_class)
			file << "--------------------------" << endl;

	}// for

	bool sucess = true;
	for (int i = 0; i < Vers; i++)
		if (in_degree[i] != -1)
			sucess = false;

	// failed
	if (sucess == false) {
		cout << "Sorry! There is no solution for your education plan." << endl;
		file.close();
		ofstream file(path, ios::trunc); // clear the file
		file << "Sorry! There is no solution for your education plan." << endl;
		file.close();
		flag = false;
		return;
	}

	cout << "Your education plan has been written into ./" << path << endl;

	delete[]in_degree;

	file.close();
}

template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>
::build_plan_v2(const int total_c, const string file_name)const {

	string path = file_name + ".txt";
	ofstream file(path);

	file << "SEMESTER" << setw(10) << "CLASS_ID" << setw(10) << "CREDIT" << endl;

	linkQueue<int>q;
	edgeNode *p;
	
	int *in_degree = new int[Vers];
	for (int i = 0; i < Vers; i++)
		in_degree[i] = 0;

	for (int i = 0; i < Vers; i++)
		for (p = verList[i].head; p != NULL; p = p->next)
			++in_degree[p->end];

	// loop for semester
	int c_every_s = total_c / this->t_sems;
	bool flag = false;
	if (c_every_s * this->t_sems == total_c)
		flag = true;

	for (int i = 1; i <= this->t_sems; i++) {

		int total_credit_ = 0;
		int c_this_s = 0;

		// check all courses that are available in this sesmester
		for (int j = 0; j < Vers; j++)
			if (in_degree[j] == 0 && !q.isinQueue(j))
				q.enQueue(j);

		bool if_no_class = true;
		while (!q.isEmpty()) {

			int course = q.getHead();
			total_credit_ += verList[course].credit;

			// can attend this course
			if (total_credit_ <= this->cre_max) {
				// to implement uniform
				if ((flag==true&&c_this_s < c_every_s)
					||(flag==false&&c_this_s<=c_every_s)) {
					q.deQueue();
					file << setw(4) << i << setw(11);
					file << verList[course].ver << setw(10);
					file << verList[course].credit << endl;

					// update in-degree
					for (p = verList[course].head; p != NULL; p = p->next)
						--in_degree[p->end];

					in_degree[course] = -1;

					++c_this_s;
					if_no_class = false;
				}

				// have reached the max number of courses
				else break;
			}// if
			else break;

		}// while

		if (!if_no_class)
			file << "--------------------------" << endl;



	}// for

	// cout << "Your education plan has been written into ./" << path << endl;

	delete[]in_degree;
	file.close();
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>
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
