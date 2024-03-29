/********************************************************************************************
 19.11.11 14:16 [SW Expert Academy] <모의 SW 역량테스트> 등산로 조성

 문제 자체는 간단했으나 평소처럼 다음좌표의 값을 전역 변수로 설정했더니 오류가 발생하였다. 
 (재귀호출 시 메모리를 절약하기 위해 함수 내부 변수를 전역으로 설정하는 것이 버릇이 되었다)
 (dfs 특성상 특정 방향 탐색 후 (_x,_y) 변수값이 바뀐 것을 모르고 오랜시간 고생하였다.)

 또, 한 가지는 탐색여부를 체크하는 visited 함수를 설정하지 않아 오류가 발생하였다.
 한 번의 탐색으로 이동한 경우 높은 곳->낮은 곳으로 이동했기 때문에 역방향으로는 탐색을
 하지 않을 것이라 생각한 것이다. 하지만, 이전 노드의 높이를 깎는 경우 역방향 탐색이 가능하였다.
 따라서, visited 함수를 선언하여 이미 탐색한 부분을 체크하니 성공할 수 있었다.
/********************************************************************************************/

#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> pos;

queue<pos> que;

int arr[10][10] = { 0, };
bool visited[10][10] = { 0, };
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int T, N, K, mou_top, answer;

// vistied 배열을 초기화하는 함수
void visited_clear() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = 0;
		}
	}
}

void dfs(int i, int j, int k, int dep) {
	if (dep > answer)
		answer = dep;

	for (int d = 0; d < 4; d++) {
		int _x = i + dx[d];
		int _y = j + dy[d];
		if (_x<1 || _y<1 || _x>N || _y>N || visited[_x][_y])
			continue;
		
		if (arr[i][j] > arr[_x][_y]) {
			visited[_x][_y] = 1;
			dfs(_x, _y, k, dep + 1);
			visited[_x][_y] = 0;
		}
		else if (arr[i][j] > arr[_x][_y] - k) {
			int temp = arr[_x][_y];
			arr[_x][_y] = arr[i][j] - 1;
			visited[_x][_y] = 1;
			dfs(_x, _y, 0, dep + 1); // 산 봉우리를 깎은 경우, k = 0.
			arr[_x][_y] = temp;
			visited[_x][_y] = 0;
		}
	}
}

// 가장 높은 봉우리를 찾아, 큐에 담는 함수
void search_top() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (arr[i][j] == mou_top)
				que.push({ i, j });
		}
	}
}

void solve() {
	search_top();
	while (!que.empty()) {
		pos p = que.front();
		que.pop(); 
		visited_clear();
		visited[p.first][p.second] = 1;
		dfs(p.first, p.second, K, 1);
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> K;
		mou_top = 0; answer = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> arr[i][j];
				if (arr[i][j] > mou_top)
					mou_top = arr[i][j];
			}
		}	
		solve();
		cout << "#" << tc << " " << answer << endl;
	}
}

int main(void) {
	init();
	return 0;
}
