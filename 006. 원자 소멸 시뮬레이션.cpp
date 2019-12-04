/********************************************************************************************
 19.11.25 16:35 [SW Expert Academy] <모의 SW 역량테스트> 원자 소멸 시뮬레이션

먼저, 임의의 두 원자를 선택하여 충돌하는지 판별한다.
이후, 두 원자가 충돌하는 시간을 오름 차순으로 정렬하여 우선순위 큐에 삽입한다.
마지막으로 큐에서 하나씩 꺼내면서 소멸되지 않은 원자의 경우(에너지가 방출x) 총 에너지를 증가시켜준다.

해당 문제는 두 원자가 충돌하는지 판별하는 것이 핵심이었다.
처음에는 단순히 두 원자의 거리가 줄어드는 것만 고려했지만, 0이 안되는 경우가 있었다.
(서로 반대방향이지만 행이나 열이 다른경우)
따라서, 두 원자를 직접 이동시켜 같은 좌표에 위치하는지 검사하는 방법을 통해 판별할 수 있었다.
 ********************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

struct Atom {
	int x, y, dir, energy;
	float ct;
};

struct Crash {
	int i, j;
	float t;

	// 충돌시간을 오름차순으로 정렬
	bool operator <(const Crash &c)const {
		return this->t > c.t;
	}
};
vector<Atom> vec;
priority_queue<Crash> que;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };
int T, N, ipt1, ipt2, ipt3, ipt4;
int total_energy;

// 두 원자가 만나는지 판별하는 함수이다.
// 두 원자사이의 거리의 반 만큼 각각 이동하여 같은 위치이면 충돌한다.
void isCloser(int i, int j) {
	float dis = (float)(abs(vec[i].x - vec[j].x) + abs(vec[i].y - vec[j].y));

	float new_x1 = (float)(vec[i].x + (dx[vec[i].dir] * (dis / 2)));
	float new_y1 = (float)(vec[i].y + (dy[vec[i].dir] * (dis / 2)));
	float new_x2 = (float)(vec[j].x + (dx[vec[j].dir] * (dis / 2)));
	float new_y2 = (float)(vec[j].y + (dy[vec[j].dir] * (dis / 2)));

	// 두 원자가 만날 경우
	if (new_x1 == new_x2 && new_y1 == new_y2) {
		que.push({ i, j, dis / 2 });
	}
}

void solve() {
	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			isCloser(i, j);
		}
	}

	while (!que.empty()) {
		Crash c = que.top();
		que.pop();

		// 3이상의 홀수 개수의 원자가 동시에 충돌할 경우를 고려한다.
		if (vec[c.i].ct == vec[c.j].ct || vec[c.i].ct == c.t || vec[c.j].ct == c.t) {
			if (!vec[c.i].ct) { total_energy += vec[c.i].energy; vec[c.i].ct = c.t; }
			if (!vec[c.j].ct) { total_energy += vec[c.j].energy; vec[c.j].ct = c.t; }
		}
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> ipt1 >> ipt2 >> ipt3 >> ipt4;
			vec.push_back({ ipt1, ipt2, ipt3, ipt4, 0.0 });
		}
		total_energy = 0;
		solve();
		cout << "#" << tc << " " << total_energy << endl;
		vec.clear();
	}
}

int main(void) {
	init();
	return 0;
}
