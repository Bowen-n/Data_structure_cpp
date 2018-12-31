#include "adjListGraph.h"
#include <string>
#include <vector>

void split_str(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

int main() {

	int semester;
	int credit_hour;
	int course;

	cout << "Please input semester, credit hour,";
	cout << "number of courses:" << endl;
	cin >> semester >> credit_hour >> course;
	cout << "Please input " << course << " courses' ID";
	cout << "Credits, Prerequisite course(if none, input @):" << endl;

	string *c_id = new string[course];
	int *c_cred = new int[course];
	string *c_pre = new string[course];
	for (int i = 0; i < course; i++) {
		cin >> c_id[i];
		cin >> c_cred[i];
		cin >> c_pre[i];
	}

	// initialize course map
	adjListGraph<string, int> c_map(course, semester
		, credit_hour, c_cred, c_id);

	// find the prerequisite course
	// and construct the connection in the map
	for (int i = 0; i < course; i++) {
		// no pre course
		if (c_pre[i][0] == '@')
			continue;
		vector<string>tmp; // store pre courses
		split_str(c_pre[i], tmp, ",");
		for (int j = 0; j < tmp.size(); j++)
			c_map.insert(tmp[j], c_id[i], 0);
	}

	system("cls");
	// c_map.show_graph();

	cout << "Please input the file's name(omit the file suffix):" << endl;

	string file_path; cin >> file_path;

	cout << endl;
	// input method
	cout << "Please input the 1 or 2:" << endl;
	cout << "1. Courses are arranged in all semesters." << endl;
	cout << "2. Courses are mainly in the first few semesters." << endl;
	int method; cin >> method;
	while (method != 1 && method != 2) {
		cout << "Error, please try again!." << endl;
		cin >> method;
	}

	switch (method) {
	case 1: {
		bool flag = true;
		c_map.build_plan_v1(file_path, flag);
		if (flag) // success
			c_map.build_plan_v2(course, file_path);
		break;
	}
	case 2: {
		bool tmp = true;
		c_map.build_plan_v1(file_path, tmp);
		break;
	}
	default:break;
	}


	delete[]c_pre;
	delete[]c_cred;
	delete[]c_id;
	return 0;
}