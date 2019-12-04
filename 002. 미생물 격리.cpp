/********************************************************************************************
 19.11.11 17:22 [SW Expert Academy] <모의 SW 역량테스트> 미생물 격리

 이미 이동을 완료한 미생물과 앞으로 이동할 미생물을 어떻게 구분할 것인지가 쟁점이였다.
 입력데이터에서 힌트를 얻어 배열이 아닌 큐에 저장하여 미생물의 정보만 바꾸는 방식을 생각하였다.
 이 때, 미생물의 수가 많은 군집이 살아남아야 하므로 우선순위 큐를 활용하였다.
 ********************************************************************************************/

#include <iostream>
#include <queue>
using namespace std;

struct Microorganism {
	int x, y, n, d; // 좌표, 수, 방향
	bool operator<(const Microorganism &m) const {	
		return this->n < m.n;
	}
};

priority_queue<Microorganism> p_que;
queue<Microorganism> que;

int selected[102][102] = { 0, };
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0 ,0, -1, 1 };
int T, N, M, K, _x, _y, _n, _d, answer;

void solve() {
	while (M-- > 0) {
		while (!p_que.empty()) {
			Microorganism m = p_que.top();
			p_que.pop();
			m.x += dx[m.d];
			m.y += dy[m.d];
			if (m.x == 0 || m.y == 0 || m.x == N-1 || m.y == N-1) { // 가장자리의 경우, 반감
				if (m.d == 0) m.d = 1;
				else if (m.d == 1) m.d = 0;
				else if (m.d == 2) m.d = 3;
				else if (m.d == 3) m.d = 2;
				m.n = m.n / 2;
			}

			if (selected[m.x][m.y] == 0) {
				selected[m.x][m.y] = m.n;
				que.push(m);
			}
			else { // 이동한 좌표에 이미 군집이 있는 경우 합쳐진다. (이 때, 상대적으로 수가 적으므로 큐에 넣지 않는다.)
				selected[m.x][m.y] += m.n;
			}
		}

		while (!que.empty()) { // 큐에서 꺼내면서 미생물의 수를 업데이트 해준다.
			Microorganism m = que.front();
			que.pop();
			m.n = selected[m.x][m.y];
			selected[m.x][m.y] = 0;
			p_que.push(m);
		}
	}

	// 마지막에 모든 군집의 미생물 수를 더해준다.
	while (!p_que.empty()) {
		answer += p_que.top().n;
		p_que.pop();
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		while (K-- > 0) {
			cin >> _x >> _y >> _n >> _d;
			p_que.push({ _x, _y, _n, _d - 1 });
		}
		answer = 0;
		solve();
		cout << "#" << tc << " " << answer << endl;
	}
}

int main(void) {
	init();
	return 0;
}
