/********************************************************************************************
 19.11.11 14:16 [SW Expert Academy] <모의 SW 역량테스트> 수영장
 
 간단한 dfs 문제다.
 1월부터 시작하여 김프로가 처음으로 수영장을 이용하는 달을 찾는다. 
 해당 달을 시작으로 1일, 1달, 3달 이용권을 사용했을 때를 가정하여 각각 dfs를 수행한다. 
 이후, 12월을 넘어갈 경우 최솟값인지 판별하여 답을 구한다.
 (answer의 초기값을 1년 이용권의 가격으로 설정하여 비교횟수를 줄였다.)
 /********************************************************************************************/

#include <iostream>

using namespace std;

int m[24] = { 0, };
int c[3] = { 0, };
int T, answer;

void dfs(int mon, int cost) {
	while (!m[mon]) {
		mon++;
		if (mon > 12) {
			if (cost < answer)
				answer = cost;
			return;
		}
	}
	dfs(mon + 1, cost + c[0] * m[mon]);
	dfs(mon + 1, cost + c[1]);
	dfs(mon + 3, cost + c[2]);
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> c[0] >> c[1] >> c[2] >> answer;
		for (int d = 0; d < 12; d++) {
			cin >> m[d];
		}
		dfs(0, 0);
		cout << "#" << tc << " " << answer << endl;
	}
}	

int main(void) {
	init();
	return 0;
}
