#pragma once

// 构造函数
// 输入参数为起始横纵坐标
Demo::Demo(int start_row, int start_col)
	:backtrace(new Stack<Position>(63)) { // 给栈动态申请63个空间
	current_pos.set_position(start_row, start_col); // 设置起始位置
	// 设置八种跳法
	jump[0].set_position(-2, 1); jump[1].set_position(-1, 2);
	jump[2].set_position(1, 2); jump[3].set_position(2, 1);
	jump[4].set_position(2, -1); jump[5].set_position(1, -2);
	jump[6].set_position(-1, -2); jump[7].set_position(-2, -1);
}

// 判断坐标合法性
// 输入为横纵坐标
// 合法返回true；否则false。
bool Demo::valid(int r, int c) {
	return (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == 0);
}

// 计算此点有几种合法的跳法
// 输入为横纵坐标
// 输出为几种跳法
int Demo::count_next_jump(int r, int c) {
	int _option = 0, _count = 0;
	int last_option = 7;
	while (_option <= last_option) {
		int _next_row = r + jump[_option].row;
		int _next_col = c + jump[_option].col;
		if (valid(_next_row, _next_col))
			++_count;
		++_option;
	}
	return _count;
}

// 寻找跳跃路径
void Demo::find_path() {
	int step = 1;
	board[current_pos.row][current_pos.col] = step;
	int option = 0;
	int last_option = 7;

	while (step != 64) { //while1
		int next_row, next_col;
		int best_row = -1, best_col = -1; // 最好的跳法位置
		int best_option = 0; // 最好的跳法
		int next_min_jump = 8; // 最少的跳法种数

		while (option <= last_option) { //while2
			// 此步已尝试过或者跳跃不合法
			if (!current_pos.options[option]) {
				++option;
				continue;
			}

			next_row = current_pos.row + jump[option].row;
			next_col = current_pos.col + jump[option].col;
			// 此步跳跃不合法，尝试下一种跳法
			if (!valid(next_row, next_col)) {
				current_pos.options[option++] = 0;
				continue;
			}

			// 此步跳跃合法
			else {
				// 计算这步跳法所到的点是否最优
				int next_jump = count_next_jump(next_row, next_col);
				if (next_min_jump > next_jump) {
					next_min_jump = next_jump; best_option = option;
					best_row = next_row; best_col = next_col;
				}
				++option;
			}// else
		}// while2

		// 如果存在可选跳法
		if (best_row != -1 && best_col != -1) {
			board[best_row][best_col] = ++step;
			current_pos.options[best_option] = 0; // 此跳法已经尝试过
			backtrace->push(current_pos);
			current_pos.row = best_row; current_pos.col = best_col;
			current_pos.reset_a();
		}
		// 若没有跳法可以选择
		else {
			Position previous; backtrace->pop(previous);
			board[current_pos.row][current_pos.col] = 0;
			current_pos = previous;
			--step;
		}

		option = 0;

		if (step == 64)
			for (int i = 0; i <= 7; i++) {
				for (int j = 0; j <= 7; j++)
					cout << setw(4) << board[i][j];
				cout << endl;
			}

	}// while1
}