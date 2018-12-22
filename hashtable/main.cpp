#include "closeHashTable.h"
#include "openHashTable.h"
#include <string>
#define LENGTH 30
#define OPEN_LENGTH 15

// store 30 names which is initialized in main
string name[LENGTH];

// name to integer
// sum of ascii 
int stoint(string &obj) {
	int tmp = 0;
	for (int i = 0; i < obj.length(); i++)
		tmp += obj[i];
	return tmp;
}

// count digits for a integer
int get_digits(int x) {
	int digits = 1;
	while (x /= 10)digits++;
	return digits;
}

// hash function
// mod
int mod_hash(const int &x) { return x%LENGTH; }

int mod_open_hash(const int&x) { return x%OPEN_LENGTH; }

// hash function
// square the key and take the two digits in the middle
int sqr_mid_hash(const int &x) {
	int tmp = x*x;
	int digit = get_digits(tmp);
	int divid_time = (digit >> 1) - 1;
	for (int i = 0; i < divid_time; i++)
		tmp /= 10;
	return tmp % 100;
}

// hash function
// fold with two digits
int fold_hash(const int &x) {
	int tmp = x;
	int result = 0;
	while (true) {
		if (get_digits(tmp) <= 2) {
			result += tmp;
			break;
		}

		result += tmp % 100;
		tmp /= 100;
	}
	return result % 100;
}


// test function
// print out the number of conflict and find times
void test_close(const int space, int(*f)(const int&x)) {
	// KEY is the integer for name, OTHER is the order
	closeHashTable<int, int> hash_table(space, f);

	// hash and count conflicts
	int conflict = 0;
	for (int i = 0; i < LENGTH; i++) {
		int conflict_ = 0;
		SET<int, int> tmp(stoint(name[i]), i);
		hash_table.insert(tmp, conflict_);
		conflict += conflict_;
	}
	cout << "conflict:" << conflict << endl;

	// find every name and count total find times
	// and caculate average find times
	int find_time = 0;
	for (int i = 0; i < LENGTH; i++) {
		string find_obj = name[i];
		int find_time_ = 0;
		hash_table.find(stoint(find_obj), find_time_);
		find_time += find_time_;
	}
	cout << "total find time:" << find_time << endl;
	cout << "average find time:" << double(find_time) / LENGTH << endl;
}

void test_open(const int space, int(*f)(const int &x)) {
	openHashTable<int, int> hash_table(space, f);
	for (int i = 0; i < LENGTH; i++) {
		SET<int, int> tmp(stoint(name[i]), i);
		hash_table.insert(tmp);
	}

	int find_time = 0;
	for (int i = 0; i < LENGTH; i++) {
		string find_obj = name[i];
		int find_time_ = 0;
		hash_table.find(stoint(find_obj), find_time_);
		find_time += find_time_;
	}

	cout << "total find time:" << find_time << endl;
	cout << "average find time:" << double(find_time) / LENGTH << endl;
}

// 
int main() {

	// initialize 30 names
	name[0] = "wubolun"; name[1] = "wangduan"; name[2] = "huangbangyan";
	name[3] = "wumingzhou"; name[4] = "zhangyiming"; name[5] = "xuyuanhang";
	name[6] = "wuzhou"; name[7] = "wangyulong"; name[8] = "guoyida";
	name[9] = "wangyukun"; name[10] = "changboxuan"; name[11] = "zhoujiangcheng";
	name[12] = "xieyuchong"; name[13] = "guyuhan"; name[14] = "sunzixuan";
	name[15] = "chenyiyang"; name[16] = "tanxin"; name[17] = "jinfengjun";
	name[18] = "wuqingyang"; name[19] = "chenweiying"; name[20] = "wuxugang";
	name[21] = "wuqichen"; name[22] = "jinshenou"; name[23] = "zhangchenxi";
	name[24] = "zhangjiangwei"; name[25] = "zhuqi"; name[26] = "chenxinqian";
	name[27] = "zhichen"; name[28] = "niemingjie"; name[29] = "dongchengdong";

	// Hash with mod function
	cout << "******Hash with mod function*******" << endl;
	test_close(30, mod_hash);
	cout << "***********************************" << endl << endl;

	// Hash with square_mid function
	cout << "***Hash with square mid function***" << endl;
	test_close(100, sqr_mid_hash);
	cout << "***********************************" << endl << endl;

	// Hash with fold function
	cout << "******Hash with fold function******" << endl;
	test_close(100, fold_hash);
	cout << "***********************************" << endl << endl;

	// Open hash with mod function
	cout << "****Open hash with mod function****" << endl;
	test_open(OPEN_LENGTH, mod_open_hash);
	cout << "***********************************" << endl;

	return 0;
}