/********************************************************************************************************************
 19.11.13 17:12 [SW Expert Academy] <모의 SW 역량테스트> 탈주범 검거
 
 간단한 BFS 문제이다.
 입력을 받을 때, 구조물의 종류에 따라 연결 가능한 방향을 체크하였다.
 이후, BFS를 돌면서 현재 칸과 인접한 칸이 서로 연결 가능할 경우 탐색을 지속한다.
 마지막으로 방문 노드의 개수를 통해 답을 구할 수 있었다.
 
 (내가 푼 알고리즘의 경우 visited를 체크하여 중복된 노드를 탐색하는 경우가 발생한다.
  따라서, 처음에는 cnt값을 큐에서 꺼낼 때마다 증가시켜주는 형식으로 구현하였더니 기존 답 보다 매우 큰 값이 출력되었다. 
  문제를 발견한 후에 큐에 탐색 노드를 집어 넣으면서 visited를 체크 해줄까 생각을 해보았다.
  하지만, 방문노드의 개수를 답으로 출력하는 것이 더 간단할 것으로 생각하여 해당방식으로 구현해 보았다.)
*********************************************************************************************************************/

#include <iostream>
#include <queue>

using namespace std;

queue<pair<int, int>> que;

bool arr[51][51][4] = { 0, }; // 동, 서, 남, 북
bool visited[51][51] = { 0, };
int T, N, M, R, C, L, ipt, cnt, qSize;

// 방문한 구역의 개수 = 답
void cal() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (visited[i][j]) cnt++;
		}
	}
}

// 초기화 하는 함수
void clear_arr() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			arr[i][j][0] = arr[i][j][1] = arr[i][j][2] = arr[i][j][3] = 0;
			visited[i][j] = 0;
		}
	}
	while (!que.empty()) que.pop();
}

void bfs() {
	int t = 1;
	while (t < L + 1) {
		qSize = que.size();
		while (qSize-- > 0) {
			pair<int, int> p = que.front();
			que.pop(); 
			visited[p.first][p.second] = 1; 
			// 현재 칸과 인접한 칸이 연결이 가능할 경우, 큐에 추가
			if (arr[p.first][p.second][0] && arr[p.first][p.second + 1][1] && !visited[p.first][p.second + 1]) que.push({ p.first, p.second + 1 });
			if (arr[p.first][p.second][1] && arr[p.first][p.second - 1][0] && !visited[p.first][p.second - 1]) que.push({ p.first, p.second - 1 });
			if (arr[p.first][p.second][2] && arr[p.first + 1][p.second][3] && !visited[p.first + 1][p.second]) que.push({ p.first + 1, p.second });
			if (arr[p.first][p.second][3] && arr[p.first - 1][p.second][2] && !visited[p.first - 1][p.second]) que.push({ p.first - 1, p.second });
		}
		t++;
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> R >> C >> L;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				cin >> ipt;
				if (ipt == 1) { arr[i][j][0] = arr[i][j][1] = arr[i][j][2] = arr[i][j][3] = 1; }
				else if (ipt == 2) { arr[i][j][2] = arr[i][j][3] = 1; }
				else if (ipt == 3) { arr[i][j][0] = arr[i][j][1] = 1; }
				else if (ipt == 4) { arr[i][j][0] = arr[i][j][3] = 1; }
				else if (ipt == 5) { arr[i][j][0] = arr[i][j][2] = 1; }
				else if (ipt == 6) { arr[i][j][1] = arr[i][j][2] = 1; }
				else if (ipt == 7) { arr[i][j][1] = arr[i][j][3] = 1; }
			}
		}
		cnt = 0; 
		que.push({ R + 1, C + 1 });
		bfs(); cal();
		cout << "#" << tc << " " << cnt << endl;
		clear_arr();
	}
}

int main(void) {
	init();
	return 0;
}
