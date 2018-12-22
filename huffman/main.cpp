#include "hfTree.h"

// prompt the menu
// return the command by user
char promptMenu() {
	cout << endl;
	cout << "*****************************************" << endl;
	cout << "   Huffman Encoding and Decoding System" << endl;
	cout << "*****************************************" << endl;
	cout << "(1) Please input I/i for Intialization" << endl;
	cout << "(2) Please input E/e for Encoding" << endl;
	cout << "(3) Please input D/d for Decoding" << endl;
	cout << "(4) Please input P/p for Code Printing" << endl;
	cout << "(5) Please input T/t for Tree Printing" << endl;
	cout << "(6) Please input M/m for Message Encoding" << endl;
	cout << "(7) Please input Q/q for Quit" << endl;
	cout << "Your input:";
	char command; cin >> command;
	while (command != 'I' && command != 'i'
		&& command != 'E' && command != 'e'
		&& command != 'D' && command != 'd'
		&& command != 'P' && command != 'p'
		&& command != 'T' && command != 't'
		&& command != 'M' && command != 'm'
		&& command != 'Q' && command != 'q') {
		cout << "Invalid input! Please try again." << endl;
		cin >> command;
	}
	return command;
}

// pompt for error UNINITIALZED
void promptUninitialized() {
	cout << endl << "Failed!" << endl;
	cout << "The huffman tree hasn't been initialized." << endl;
}

// main
int main() {
	char command = 0;
	hfTree tree;
	bool flag_for_initialize = false;
	bool flag_for_encode = false;

	while (true) {

		command = promptMenu();

		if (command == 'I' || command == 'i') {
			cout << endl << "Please input the size of the character set:";
			int size_; cin >> size_;
			cin.get(); tree.setSize_v_w(size_);
			tree.initialize();
			flag_for_initialize = true;
			cout << "Done!" << endl;
			cout << "The details of the huffman tree has been stored in ./hfmTree.txt" << endl;
			//cout << "******************************************" << endl;
		}

		else if (command == 'E' || command == 'e') {
			// initialized or not
			if (flag_for_initialize) {
				cout << endl << "Encoding......" << endl;
				hfTree::hfCode *result = new hfTree::hfCode[tree.getSize()];
				assert(result != NULL);
				tree.getCode(result);
				string source = "./plainFile.txt";
				tree.encode(source, result);
				flag_for_encode = true;
				cout << "Done!" << endl;
				cout << "The data in ./plainFile.txt has been encoded into ./codeFile.txt" << endl;
				delete[]result;
			}
			else
				promptUninitialized();
		}

		else if (command == 'D' || command == 'd') {
			// initialized or not
			if (flag_for_initialize) {
				cout << endl << "Decoding......" << endl;
				string source = "./codeFile.txt";
				tree.decode(source);
				cout << "Done!" << endl;
				cout << "The data in ./codeFile.txt has been decoded into ./textFile.txt" << endl;
			}
			else
				promptUninitialized();
		}

		else if (command == 'P' || command == 'p') {
			if (flag_for_encode) {
				// having encoded or not
				cout << endl << "ENCODE Result:" << endl;
				string source = "./codeFile.txt";
				tree.codePrint(source);
				cout << "Writting out......" << endl;
				cout << "Done!" << endl;
				cout << "The code has been written into ./codePrint.txt" << endl;
			}
			else {
				cout << endl << "Failed!" << endl;
				cout << "The data hasn't been encoded." << endl;
			}
		}

		else if (command == 'T' || command == 't') {
			// initialized or not
			if (flag_for_initialize) {
				cout << endl << "Huffman tree:" << endl;
				tree.treePrint();
				cout << "Writting out......" << endl;
				cout << "Done!" << endl;
				cout << "The huffman tree has been written into ./treePrint.txt" << endl;
			}
			else
				promptUninitialized();
		}

		else if (command == 'M' || command == 'm') {
			string source = "./data.txt";
			tree.encode_for_message(source);
			flag_for_encode = true;
			flag_for_initialize = true;
			cout << "The message in " << source << " has been encoded into ./codeFile.txt" << endl;
			source = "./codeFile.txt";
			// cout << "Decoding......" << endl;
			// tree.decode_for_message(source);
			// cout << "Done!" << endl;
			// cout << "The code in ./codoFile.txt has been decoded into ./textFile.txt" << endl;
		}

		else {// quit
			cout << endl << "Thanks for using!" << endl;
			break;
		}

	}

	return 0;
}

