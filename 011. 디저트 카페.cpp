/********************************************************************************************
19.12.09 15:15 [SW Expert Academy] <모의 SW 역량테스트> 디저트 카페

약간 복잡한 dfs 문제이다.
대각선 방향으로 탐색을 하되, 이미 방문했던 디저트 종류일 경우에는 되돌아간다.
이 때, 방문했던 디저트들의 경우에는 문자열 형태로 저장하였다.

또한, 오른쪽 대각선 윗방향으로 움직일 경우에는 시작점으로 되돌아가기 위해 얼만큼 올라가야 하는지,
얼마나 꺾어야 하는지 정해져 있다. 
따라서, 이동 거리를 계산한 후 시작점으로 되돌아 올 경우 최댓값인지 검사하여 답을 구하였다.
********************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int arr[21][21] = { 0, };
int T, N, start_i, start_j, answer;

// 초기화하는 함수
void clear_arr() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			arr[i][j] = 0;
		}
	}
}

bool find_n(char ch, string str) {
	for (char c : str) {
		if (ch == c)
			return true;
	}
	return false;
}

// 방문 노드 좌표(i, j)와 이동방향, 문자열
void dfs(int i, int j, int dir, string str) {
	// 왼쪽 아랫 방향
	if (dir == 1) {
		if (i < N-1 && j > 1 && !find_n(arr[i + 1][j - 1], str)) {
			dfs(i + 1, j - 1, 1, str + (char)arr[i + 1][j - 1]);
		}
		if (i != start_i && !find_n(arr[i + 1][j + 1], str)) {
			dfs(i + 1, j + 1, 2, str + (char)arr[i + 1][j + 1]);
		}
	}
	// 오른쪽 아랫 방향
	else if (dir == 2) {
		if (i < N  && j < N - 1 && !find_n(arr[i + 1][j + 1], str)) {
			dfs(i + 1, j + 1, 2, str + (char)arr[i + 1][j + 1]);
		}
		if (!find_n(arr[i - 1][j + 1], str)) {
			dfs(i - 1, j + 1, 3, str + (char)arr[i - 1][j + 1]);
		}
	}
	
	// 오른쪽 윗 방향
	else if (dir == 3) {
		if (j < N && abs(start_i - i) != abs(start_j - j) && !find_n(arr[i - 1][j + 1], str)) {
			dfs(i - 1, j + 1, 3, str + (char)arr[i - 1][j + 1]);
		}
		else if (abs(start_i - i) == abs(start_j - j) && !find_n(arr[i - 1][j - 1], str)) {
			dfs(i - 1, j - 1, 4, str + (char)arr[i - 1][j - 1]);
		}
		else if (i - 1 == start_i && j - 1 == start_j && str.length() > answer) {
			answer = str.length();
		}
	}

	// 왼쪽 윗 방향
	else if (dir == 4) {
		int _i = i, _j = j;
		while (_i != start_i && _j != start_j && !find_n(arr[_i - 1][_j - 1], str)) {
			_i--; _j--;
			str += arr[_i][_j];
		}
		if (_i - 1 == start_i && _j - 1 == start_j && str.length() > answer) {
			answer = str.length();
		}
	}
}

void solve() {
	for (int i = 1; i <= N - 2; i++) {
		for (int j = 2; j <= N - 1; j++) {
			start_i = i, start_j = j;
			string s = "";
			s += arr[i][j];
			dfs(i, j, 1, s);
		}
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> arr[i][j];
			}
		}
		answer = 0;
		solve();
		if (answer == 0) answer = -1;
		cout << "#" << tc << " " << answer << endl;
		clear_arr();
	}
}

int main(void) {
	init();
	return 0;
}
