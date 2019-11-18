/********************************************************************************************
 19.11.18 15:01 [SW Expert Academy] <모의 SW 역량테스트> 무선 충전
 
 최근에 푼 문제 중 가장 오랜시간이 걸렸다.
 처음에는 각 배터리의 충전량을 내림차순으로 정렬하여 풀었다. 
 임의의 사용자가 해당 배터리 충전 범위내에 있는 경우 충전하는 방식으로 구현하였다. 
 하지만, 상대적으로 낮은 충전량의 배터리를 선택해야 할 경우도 있었다. 
 또한, 사용자 A가 충전하고 B가 충전하는 방식이 아닌 두 사용자 동시에 고려해야하기 때문에 어려웠다.
 따라서, 모든 조건문을 검사하기 보다는 완전탐색을 택하여 최소한의 조건만 따지도록 구현하였다.
 ********************************************************************************************/
 
#include <iostream>
#include <vector>
using namespace std;

struct Battery {
	int x, y, range, power;
};

vector<Battery> bt;
int mv[2][101] = { 0, };
int dx[5] = { 0, -1, 0, 1, 0 };
int dy[5] = { 0, 0, 1, 0, -1 };
int T, M, A, ipt1, ipt2, ipt3, ipt4;
int total_charge, s;

void clear_arr() {
	for (int i = 0; i < 2; i++) {
		for(int j = 0; j < 100; j++){
			mv[i][j] = 0;
		}
	}
}

void solve() {
	int p1_x = 1, p1_y = 1, p2_x = 10, p2_y = 10;

	for (int idx = 0; idx <= M; idx++) {
		p1_x += dx[mv[0][idx]];
		p1_y += dy[mv[0][idx]];
		p2_x += dx[mv[1][idx]];
		p2_y += dy[mv[1][idx]];

		s = 0;

		for (int i = 0; i < bt.size(); i++) {
			// 하나의 사용자만 충전이 가능한 경우
			if (abs(p1_x - bt[i].x) + abs(p1_y - bt[i].y) <= bt[i].range && bt[i].power > s) {
				s = bt[i].power;
			}
			if (abs(p2_x - bt[i].x) + abs(p2_y - bt[i].y) <= bt[i].range && bt[i].power > s) {
				s = bt[i].power;
			}
			for (int j = 0; j < bt.size(); j++) {
				// 두 사용자 모두 충전이 가능한 경우
				if (abs(p1_x - bt[i].x) + abs(p1_y - bt[i].y) <= bt[i].range && abs(p2_x - bt[j].x) + abs(p2_y - bt[j].y) <= bt[j].range) {
					if (i == j) 
						continue;
					else if( bt[i].power + bt[j].power > s){
						s = bt[i].power + bt[j].power;
					}
				}
			}
		}

		total_charge += s;
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> M >> A;
		for (int idx = 0; idx < 2; idx++) {
			for (int d = 1; d <= M; d++) {
				cin >> mv[idx][d];
			}
		}
		for (int b = 0; b < A; b++) {
			cin >> ipt1 >> ipt2 >> ipt3 >> ipt4;
			bt.push_back({ ipt2 , ipt1, ipt3, ipt4});
		}
		total_charge = 0;
		solve();
		cout << "#" << tc << " " << total_charge << endl;

		bt.clear();
		clear_arr();
	}
}

int main(void) {
	init();
	return 0;
}
