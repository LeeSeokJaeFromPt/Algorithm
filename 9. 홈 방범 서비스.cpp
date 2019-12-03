/********************************************************************************************
19.12.04 15:30 [SW Expert Academy] <모의 SW 역량테스트> 홈 방범 서비스

브루트 포스를 사용하였다.
맵의 크기가 제한이 있는 만큼 K 값을 증가시키며 답을 찾도록 하였다.
이 때, 브루트 포스 특성상 시간이 많이 걸리는 단점이 존재하였다.
********************************************************************************************/
#include <iostream>
#include <cstdlib>
using namespace std;

int cost[22] = { 0, };
int arr[21][21] = { 0, };

int T, N, M, answer;

void clear_arr() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			arr[i][j] = 0;
		}
	}
}

void cal(int x, int y) {
	int k = 1, cnt;
	while (k <= 20) {
		cnt = 0;

		// k값에 따른 서비스 가능한 가구의 수
		for (int i = x - k; i <= x + k; i++) {
			for (int j = y - k; j <= y + k; j++) {
				if (abs(x - i) + abs(y - j) > k)
					continue;
				else if (i < 1 || j < 1 || i > N || j > N)
					continue;
				else if (arr[i][j])
					cnt++;
			}
		}

		if (cost[k + 1] <= (cnt * M) && cnt > answer) {
			answer = cnt;
		}
		k++;
	}

}

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cal(i, j);
		}
	}
}


void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> arr[i][j];
			}
		}

		// cost 배열 초기화
		for (int i = 1; i <= 21; i++) {
			cost[i] = (i * i) + ((i - 1)*(i - 1));
		}

		answer = 1;
		solve();
		cout << "#" << tc << " " << answer << endl;
		clear_arr();
	}
}

int main(void) {
	init();
	return 0;
}
