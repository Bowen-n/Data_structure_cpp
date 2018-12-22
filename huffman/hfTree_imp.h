#pragma once
// implementation of function in huffman tree


// initialize length, v, w
// input: the size of character set
void hfTree::setSize_v_w(const int &size) {
	length = size << 1;
	cout << "Please input " << size << " characters:"; 
	v = new char[size + 1]; assert(v != NULL);
	for (int i = 0; i < size; i++)
		v[i] = cin.get();
	cout << "Please input "<<size<<" weights:";
	w = new double[size]; assert(w != NULL);
	for (int i = 0; i < size; i++)
		cin >> w[i];
};


// initialize elem (construct the huffman tree)
void hfTree::initialize() {

	double min1_w, min2_w;
	int min1_sub, min2_sub;
	int size = length >> 1;

	elem = new Node[length]; assert(elem != NULL);

	for (int i = size; i < length; i++) {
		elem[i].weight = w[i - size];
		elem[i].data = v[i - size];
		elem[i].parent = elem[i].right = elem[i].left = 0;
	}

	// merge
	for (int i = size - 1; i > 0; i--) {
		min1_w = min2_w = MAX_DOUBLE;
		min1_sub = min2_sub = 0;
		for (int j = i + 1; j < length; j++) {
			if (elem[j].parent == 0)
				if (elem[j].weight < min1_w) {
					min2_w = min1_w;
					min1_w = elem[j].weight;
					min2_sub = min1_sub;
					min1_sub = j;
				}
				else if (elem[j].weight < min2_w) {
					min2_w = elem[j].weight;
					min2_sub = j;
				}
		}

		elem[i].weight = min1_w + min2_w; elem[i].parent = 0;
		elem[i].left = min1_sub; elem[i].right = min2_sub;
		elem[min1_sub].parent = i; elem[min2_sub].parent = i;

	}

	// write to hfmTree.txt
	ofstream ofile;
	ofile.open("./hfmTree.txt");
	// title
	ofile << "Value" << setw(7)
		<< "Weight" << setw(7)
		<< "Parent" << setw(7)
		<< "Left" << setw(7)
		<< "Right" << endl;
	// value
	for (int i = 1; i < length; i++) {
		if (i >= (length >> 1))
			if (elem[i].data == '\n')
				ofile << "\\n" << setw(7);
			else
				ofile << elem[i].data << setw(8);
		else
			ofile << " " << setw(8);
		ofile << elem[i].weight << setw(8)
			<< elem[i].parent << setw(8)
			<< elem[i].left << setw(8)
			<< elem[i].right << endl;
	}
	ofile.close();
}

// get the code and store it into result[]
// input: an hfCode array to store the code
void hfTree::getCode(hfCode result[]) {
	int size = length >> 1;
	int p, s;

	for (int i = size; i < length; i++) {
		result[i - size].data = elem[i].data;
		result[i - size].code = "";
		p = elem[i].parent; s = i;
		while (p) {
			// left add '0'
			if (elem[p].left == s)
				result[i - size].code = '0' + result[i - size].code;
			// right add '1'
			else
				result[i - size].code = '1' + result[i - size].code;
			s = p;
			p = elem[p].parent;
		}
	}
}

// encode the file in source(path)
// and store the result in ./codeFile.txt
// input: 1. path of the file
//        2. the result of getCode()
void hfTree::encode(string source, const hfCode result[]) {
	int size = length >> 1;
	ifstream ifile; ifile.open(source);
	ofstream ofile; ofile.open("./codeFile.txt");
	while (true) {
		char tmp = ifile.get();
		// search tmp in result[]
		for (int i = 0; i < size; i++) 
			if (tmp == result[i].data) {
				ofile << result[i].code;
				break;
			}
		if (ifile.eof())break;
	}
	ifile.close();
	ofile.close();
}

// decode the data in source(path)
// and store the result in ./textFile.txt
// input: the path of data
void hfTree::decode(string source) {
	ifstream ifile; ifile.open(source);
	ofstream ofile; ofile.open("./textFile.txt");
	// overall loop
	while (true) {
		// start from root
		int sub = 1; // current subscript
		// code loop
		while (true) {
			char tmp = ifile.get();
			if (tmp == '0') // go to left child
				sub = elem[sub].left;
			else // tmp == '1' go to right child
				sub = elem[sub].right;
			if (elem[sub].right == 0) { // reach leaf node
				ofile << elem[sub].data;
				break;
			}
		}
		if (ifile.eof())break;
	}
	ifile.close();
	ofile.close();
}

// print the coding result in source(path)
// and store it in ./codePrint.txt
// input: the path of the result
void hfTree::codePrint(string source) {
	ifstream ifile; ifile.open(source);
	ofstream ofile; ofile.open("./codePrint.txt");
	int count = 0;
	while (true) {
		char tmp = ifile.get();
		cout << tmp; ofile << tmp; ++count;
		if (count % 50 == 0) {
			cout << endl;
			ofile << endl;
		}
		if (ifile.eof()) break;
	}
	cout << endl;
	ifile.close();
	ofile.close();
}

// recursion for treePrint()
void hfTree::treePrint_recursion(int pos, string space, ofstream&ofile) {
	// terminal
	if (pos == 0)
		return;

	space += "   ";

	// print the right child
	treePrint_recursion(elem[pos].right, space, ofile);

	// print current node
	cout << space << elem[pos].weight;
	ofile << space << elem[pos].weight;
	// deal with '\n'
	if (elem[pos].left == 0) {
		if (elem[pos].data == '\n') {
			cout << "(\\n)";
			ofile << "(\\n)";
		}
		else {
			cout << "(" << elem[pos].data << ")";
			ofile << "(" << elem[pos].data << ")";
		}
	}
	cout << endl; ofile << endl;

	//print the left child
	treePrint_recursion(elem[pos].left, space, ofile);
}

// print the huffman tree
// and store it in ./treePrint.txt
void hfTree::treePrint() {
	string space = "";
	ofstream ofile;
	ofile.open("./treePrint.txt");
	treePrint_recursion(1, space, ofile);
	cout << endl; ofile << endl;
	ofile.close();
}

// construct a huffman tree according to the input data
// encode the data using this tree
// and store the result into ./codeFile.txt
void hfTree::encode_for_message(string source) {

	ifstream ifile;
	ifile.open(source);

	cout << endl << "Counting the frequency......" << endl;

	// count the frequency of every character
	int count_[128] = { 0 };
	for(int i=0;i<128;i++)
		count_[i]=0;
	while (true) {
		char tmp = ifile.get();
		if(tmp>=0&&tmp<=127)
			count_[tmp]++;
		if (ifile.eof())
			break;
	}
	cout << "Done!" << endl;

	cout << "Initialing the huffman tree......" << endl;
	// initialize v and w
	int size_ = 0;
	v = new char[128]; assert(v != NULL);
	w = new double[128]; assert(w != NULL);

	for (int i = 0; i < 128; i++)
		if (count_[i] != 0) {
			v[size_] = i;
			w[size_] = count_[i];
			++size_;
		}
	
	// initialize length
	length = size_ << 1;
	//cout << "Initialing the huffman tree2......" << endl;
	initialize();
	cout << "Done!" << endl;

	// encode
	cout << "Encoding......" << endl;
	hfCode *result = new hfCode[size_];
	assert(result != NULL);
	getCode(result);
	encode(source, result);
	cout << "Done!" << endl;

	delete[]result;
}

// decode the message which is encoded just now
void hfTree::decode_for_message(string source) {
	decode(source);
}

// print elem (for debugging)
void hfTree::showMemory() {
	cout << endl;
	for (int i = 1; i < length; i++) {
		cout << elem[i].weight << setw(3);
		cout << elem[i].parent << setw(3);
		cout << elem[i].left << setw(3);
		cout << elem[i].right << setw(3);
		cout << endl;
	}
}
