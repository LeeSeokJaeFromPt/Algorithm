/********************************************************************************************
19.12.05 10:08 [SW Expert Academy] <모의 SW 역량테스트> 보호 필름

약간 복잡한 dfs 문제이다.
각 행을 'A'또는 'B로 치환하여 검사한 후, 정답이 아닐경우에는 원위치 시켜준다.
이 때, 치환을 하고 재귀호출을 하는 과정에서 상대적으로 시간이 오래 걸리게 된다.

또한, chg(치환한 행의 갯수) 값이 증가할 때 마다 각 행을 다시 치환하는 반복 작업이 수행된다.
이는 dfs의 구조를 변경하여 특정 행을 치환 후 검사하는 방식으로 바꿀 수 있을 것 같다.
(구체적으로는 특정 행을 치환했을 때, 해당 상태에서의 cnt값을 chg 값으로 설정하고 리턴하거나
다시 dfs함수를 재귀호출하여 반복 작업 하는 것을 의미한다.)
********************************************************************************************/

#include <iostream>
using namespace std;

int arr[14][21] = { 0, };
int cpy_arr[14][21] = { 0, };
bool is_changed[14] = { 0, };
int T, D, W, K, answer;
int chg;

void clear_arr() {
	for (int i = 1; i <= D; i++) {
		for (int j = 1; j <= W; j++) {
			arr[i][j] = 0;
		}
	}
}

// 각 행을 검사
bool chk_row(int c) {
	for (int i = 1; i <= D - (K - 1); i++) {
		bool flag = true;
		for (int h = i; h < i + (K - 1); h++) {
			if (arr[h][c] != arr[h + 1][c]) {
				flag = false;
				break;
			}
		}
		if (flag)
			return true;
	}
	return false;
}

// 각 열을 검사
bool chk_col() {
	for (int j = 1; j <= W; j++) {
		if (!chk_row(j))
			return false;
	}
	return true;
}

void dfs(int idx, int cnt) {
	// idx 번째 행을 'A'로 바꾸었을 때
	for (int j = 1; j <= W; j++) {
		cpy_arr[idx][j] = arr[idx][j];
		arr[idx][j] = 0;
	}
	if (cnt == chg) {
		if (chk_col()) {
			answer = cnt;
			return;
		}
	}
	else {
		for (int i = idx + 1; i <= D; i++) {
			if (!is_changed[i]) {
				is_changed[i] = 1;
				dfs(i, cnt + 1);
				is_changed[i] = 0;
			}
		}
	}


	// idx 번째 행을 'B'로 바꾸었을 때
	for (int j = 1; j <= W; j++) {
		arr[idx][j] = 1;
	}
	if (cnt == chg) {
		if (chk_col()) {
			answer = cnt;
			return;
		}
	}
	else {
		for (int i = idx + 1; i <= D; i++) {
			if (!is_changed[i]) {
				is_changed[i] = 1;
				dfs(i, cnt + 1);
				is_changed[i] = 0;
			}
		}
	}

	// idx 번째 행 원위치
	for (int j = 1; j <= W; j++) {
		arr[idx][j] = cpy_arr[idx][j];
		cpy_arr[idx][j] = 0;
	}
}


void solve() {
	if (chk_col())
		return;
	
	chg = 1;
	while (!answer) {
		for (int i = 1; i <= D; i++) {
			is_changed[i] = 1;
			dfs(i, 1);
			is_changed[i] = 0;
		}
		chg++;
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> D >> W >> K;	
		for (int i = 1; i <= D; i++) {
			for (int j = 1; j <= W; j++) {
				cin >> arr[i][j];
			}
		}
		answer = 0;
		solve();
		cout << "#" << tc << " " << answer << endl;
		clear_arr();
	}
}

int main(void) {
	init();
	return 0;
}
