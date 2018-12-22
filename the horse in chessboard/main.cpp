#include "Demo.h"

// Ö÷º¯Êý
int main(){
	int start_row, start_col;
	cout << "Please input the start position:";
	cin >> start_row >> start_col;
	Demo _demo(start_row, start_col);
	_demo.find_path();
	return 0;
}