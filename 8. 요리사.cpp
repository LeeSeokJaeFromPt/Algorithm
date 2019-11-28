/********************************************************************************************
 19.11.28 13:30 [SW Expert Academy] <모의 SW 역량테스트> 요리사
 
 간단한 dfs 문제이다.
 각 식재료의 궁합을 조합으로 구한 후, 시너지를 계산하여 최솟값을 구한다.
 이 때, 조합을 구하기위해 dfs를 사용하였다.
 ********************************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

int arr[17][17] = { 0, };
bool selected[17] = { 0, };
int T, N, total_sum, answer;

void cl() {
	for (int i = 1; i <= N; i++) {
		selected[i] = 0;
		for (int j = 1; j <= N; j++) {
			arr[i][j] = 0;
		}
	}
}

void cal() {
	int s1 = 0, s2 = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (selected[i] && selected[j] && i != j) {
				s1 += arr[i][j];
			}
			else if (!selected[i] && !selected[j] && i != j) {
				s2 += arr[i][j];
			}
		}
	}

	if (abs(s1 - s2)< answer) {
		answer = abs(s1 - s2);
	}
}

void dfs(int idx, int cnt) {
	if (cnt == N / 2) {
		cal();
		return; 
	}
	for (int i = idx + 1; i <= N; i++) {
		selected[i] = 1;
		dfs(i, cnt + 1);
		selected[i] = 0;
	}
}


void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		total_sum = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> arr[i][j];
				total_sum += arr[i][j];
			}
		}
		answer = total_sum;
		selected[1] = 1;
		dfs(1, 1);
		cout << "#" << tc << " "  << answer << endl;
	}
}

int main(void) {
	init();
	return 0;
}
