#pragma once

// ���캯��
// �������Ϊ��ʼ��������
Demo::Demo(int start_row, int start_col)
	:backtrace(new Stack<Position>(63)) { // ��ջ��̬����63���ռ�
	current_pos.set_position(start_row, start_col); // ������ʼλ��
	// ���ð�������
	jump[0].set_position(-2, 1); jump[1].set_position(-1, 2);
	jump[2].set_position(1, 2); jump[3].set_position(2, 1);
	jump[4].set_position(2, -1); jump[5].set_position(1, -2);
	jump[6].set_position(-1, -2); jump[7].set_position(-2, -1);
}

// �ж�����Ϸ���
// ����Ϊ��������
// �Ϸ�����true������false��
bool Demo::valid(int r, int c) {
	return (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == 0);
}

// ����˵��м��ֺϷ�������
// ����Ϊ��������
// ���Ϊ��������
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

// Ѱ����Ծ·��
void Demo::find_path() {
	int step = 1;
	board[current_pos.row][current_pos.col] = step;
	int option = 0;
	int last_option = 7;

	while (step != 64) { //while1
		int next_row, next_col;
		int best_row = -1, best_col = -1; // ��õ�����λ��
		int best_option = 0; // ��õ�����
		int next_min_jump = 8; // ���ٵ���������

		while (option <= last_option) { //while2
			// �˲��ѳ��Թ�������Ծ���Ϸ�
			if (!current_pos.options[option]) {
				++option;
				continue;
			}

			next_row = current_pos.row + jump[option].row;
			next_col = current_pos.col + jump[option].col;
			// �˲���Ծ���Ϸ���������һ������
			if (!valid(next_row, next_col)) {
				current_pos.options[option++] = 0;
				continue;
			}

			// �˲���Ծ�Ϸ�
			else {
				// �����ⲽ���������ĵ��Ƿ�����
				int next_jump = count_next_jump(next_row, next_col);
				if (next_min_jump > next_jump) {
					next_min_jump = next_jump; best_option = option;
					best_row = next_row; best_col = next_col;
				}
				++option;
			}// else
		}// while2

		// ������ڿ�ѡ����
		if (best_row != -1 && best_col != -1) {
			board[best_row][best_col] = ++step;
			current_pos.options[best_option] = 0; // �������Ѿ����Թ�
			backtrace->push(current_pos);
			current_pos.row = best_row; current_pos.col = best_col;
			current_pos.reset_a();
		}
		// ��û����������ѡ��
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