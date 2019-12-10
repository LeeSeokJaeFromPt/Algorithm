/***************************************************************************************************
19.12.10 18:25 [SW Expert Academy] <모의 SW 역량테스트> 차량 정비소

간단한 시뮬레이션 문제이다.
각 손님의 도착시간, 접수하는데 걸리는 시간, 정비 시간이 주어지고 순서대로 수행했을 때,
특정 조건을 만족하는 손님을 찾아내는 문제이다.

각 손님은 접수하고, 수리할 때 순서대로 처리해야 하므로 큐를 사용하였다.
또한, 대기 중인 손님이 없거나, 접수 또는 수리 중인 손님이 없는 경우에는 프로그램을 종료하도록 하였다.
***************************************************************************************************/
#include <iostream>
#include <queue>
using namespace std;

struct Person{
	int num, time, reception_num;
};

// 각 항목을 수행하기 위한 대기열을 저장하는 큐
queue<Person> arrival_que, reception_que, repair_que;

int a[10] = { 0, };
int b[10] = { 0, };
Person use_a[10], use_b[10]; // 접수처 및 정비소

int T, N, M, K, A, B, ipt, answer;


// 손님이 있는지 검사하는 함수
bool isFInish() {
	if (!arrival_que.empty() || !reception_que.empty() || !repair_que.empty())
		return false;
	for (int i = 1; i <= N; i++) {
		if (use_a[i].time) return false;
	}
	for (int j = 1; j <= M; j++) {
		if (use_b[j].time) return false;
	}
	return true;
}

// 정해진 시간이 되면 손님이 도착하고, 접수 대기열에 등록된다.
void arrival(int t) {
	while (!arrival_que.empty()) {
		if (arrival_que.front().time != t)
			break;
		Person p = arrival_que.front();
		arrival_que.pop();
		reception_que.push(p);
	}
}

// 접수를 마친 손님은 정비 대기열에 등록된다.
void reception() {
	for (int i = 1; i <= N; i++) {
		if (use_a[i].time == 0 && !reception_que.empty()) {
			Person p = reception_que.front();
			reception_que.pop();
			use_a[i] = { p.num, a[i], i };
		}
		else if (use_a[i].time == 1) {
			repair_que.push(use_a[i]);
			use_a[i] = { 0, 0, 0 };
			if (!reception_que.empty()) {
				Person p = reception_que.front();
				reception_que.pop();
				use_a[i] = { p.num, a[i], i };
			}
		}
		else if(use_a[i].time > 1){
			use_a[i].time--;
		}
	}
}

// 정비를 마친 손님의 경우, 접수 번호를 확인하고 정답에 더해준다.
void repair() {
	for (int i = 1; i <= M; i++) {
		if (use_b[i].time == 0 && !repair_que.empty()) {
			Person p = repair_que.front();
			repair_que.pop();
			p.time = b[i];
			use_b[i] = p;
		}
		else if (use_b[i].time == 1) {
			if (use_b[i].reception_num == A && i == B) {
				answer += use_b[i].num;
			}
			use_b[i] = { 0, 0, 0 };
			if (!repair_que.empty()) {
				Person p = repair_que.front();
				repair_que.pop();
				p.time = b[i];
				use_b[i] = p;
			}
		}
		else if (use_b[i].time > 1) {
			use_b[i].time--;
		}
	}
}

void solve() {
	int t = arrival_que.front().time;
	while (!isFInish()) {
		arrival(t);
		reception();
		repair();
		t++;
	}
}

void init() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K >> A >> B;
		for (int i = 1; i <= N; i++) {
			cin >> a[i];
			use_a[i] = { 0, 0, 0 };
		}

		for (int j = 1; j <= M; j++) {
			cin >> b[j];
			use_b[j] = { 0, 0, 0 };
		}

		for (int k = 1; k <= K; k++) {
			cin >> ipt;
			arrival_que.push({k, ipt, 0});
		}
		answer = 0;
		solve();
		if (answer == 0) answer--; // 답이 '0'일 경우, '-1'을 출력하기 위함.
		cout << "#" << tc << " " << answer << endl;
	}
}

int main(void) {
	init();
	return 0;
}
