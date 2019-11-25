/********************************************************************************************
 19.11.25 17:20 [SW Expert Academy] <모의 SW 역량테스트> 숫자 만들기

 간단한 dfs 문제이다.
 임의의 연산자 한 개를 택하여 계산한 후, 결과값과 다음 인덱스를 인자로하여 dfs를 수행한다.
 이번 문제를 풀면서 정수형의 최댓값과 최솟값을 지정하기 위해 climits 헤더파일을 인클루드했다.
 ********************************************************************************************/

#include <iostream>
#include <climits>
using namespace std;

int oper[4] = { 0, };
int num[13] = { 0, };
int T, N, _min, _max;

// 초기화하는 함수
void clear_arr() {
	for (int i = 0; i < 4; i++) {
		oper[i] = 0;
	}

	for (int j = 1; j <= N; j++) {
		num[j] = 0;
	}
}

int calculation(int x, int y, int oper) {
	int res;
	switch (oper) {
		case 0:
			res = x + y;
			break;
		case 1:
			res = x - y;
			break;
		case 2:
			res = x * y;
			break;
		case 3:
			res = x / y;
			break;
	}
	return res;
}

void dfs(int res, int n) {
	if (n == N) {
		if (res < _min) _min = res;
		if (res > _max) _max = res;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (oper[i] > 0) {
			oper[i]--;
			dfs(calculation(res, num[n + 1], i), n + 1); //결과값과 다음 인덱스를 인자로하여 dfs 수행
			oper[i]++;
		}
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 0; i < 4; i++) {
			cin >> oper[i];
		}

		for (int j = 1; j <= N; j++) {
			cin >> num[j];
		}

		_min = INT_MAX;
		_max = INT_MIN;
		dfs(num[1], 1);
		cout << "#" << tc << " " << (_max - _min) << endl;
	}
}

int main(void) {
	init();
	return 0;
}
