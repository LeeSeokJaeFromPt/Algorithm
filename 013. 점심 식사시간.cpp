/***************************************************************************************************
19.12.14 14:36 [SW Expert Academy] <모의 SW 역량테스트> 점심 식사시간

간단한 dfs 문제이다.
각 직원이 계단을 선택하는 경우의 수를 dfs-조합으로 구한 후, 이에 따른 시간을 계산해준다.
이 때, 계단을 선택한 직원의 수가 4명 이상일 경우에는 기다리는 시간까지 고려해준다.
마지막으로 각 계단을 내려갔을 때 더 늦게 끝나는 시간을 구하고, 이 중 최솟값을 구해준다.
***************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Pos {
	int x, y, t;
};

Pos pArr[10]; // 직원 위치 저장하는 배열
Pos sArr[2];  // 계단 위치 저장하는 배열
vector<int> v1, v2; // 각 계단을 선택한 직원들을 저장하는 벡터
int T, N, ipt, pIdx, sIdx, answer;

// 배열과 벡터를 초기화하는 함수
void arr_clear() {
	for (int i = 0; i < pIdx; i++) pArr[i] = { 0, 0, 0 };
	sArr[0] = sArr[1] = { 0, 0, 0 };
	v1.clear();
	v2.clear();
}

// 시간을 계사하는 함수
void cal_time(vector<int> vec1, vector<int> vec2) {
	int max_time1 = 1, max_time2 = 1;
	if (!vec1.empty()){
		sort(vec1.begin(), vec1.end());
		if (vec1.size() >= 4) { // 계단을 선택한 인원이 4명 이상일 경우
			for (int i = 3; i < vec1.size(); i++) {
				if (vec1[i] < vec1[i - 3] + sArr[0].t)
					vec1[i] = vec1[i - 3] + sArr[0].t;
			}
		}
		max_time1 += (vec1.back() + sArr[0].t);
	}

	if (!vec2.empty()) {
		sort(vec2.begin(), vec2.end());
		if (vec2.size() >= 4) {
			for (int j = 3; j < vec2.size(); j++) {
				if (vec2[j] < vec2[j - 3] + sArr[1].t)
					vec2[j] = vec2[j - 3] + sArr[1].t;
			}
		}
		max_time2 += (vec2.back() + sArr[1].t);
	}

	max_time1 = max_time1 < max_time2 ? max_time2 : max_time1;
	if (max_time1 < answer)
		answer = max_time1;
}

// 직원과 계단 사이의 거리를 구하는 함수
int cal_distance(Pos person, Pos stair) {
	return (abs(person.x - stair.x) + abs(person.y - stair.y));
}


void dfs(int idx) {
	if (idx == pIdx) {
		cal_time(v1, v2);
		return;
	}
	v1.push_back(cal_distance(pArr[idx], sArr[0]));
	dfs(idx + 1);
	v1.pop_back();

	v2.push_back(cal_distance(pArr[idx], sArr[1]));
	dfs(idx + 1);
	v2.pop_back();
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		pIdx = 0, sIdx = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> ipt;
				if (ipt == 1) pArr[pIdx++] = { i, j, 0 };
				else if (ipt > 1) sArr[sIdx++] = { i, j, ipt };
			}
		}
		answer = 10000;
		dfs(0);
		cout << "#" << tc << " " << answer << endl;
		arr_clear();
	}
}

int main(void) {
	init();
	return 0;
}
