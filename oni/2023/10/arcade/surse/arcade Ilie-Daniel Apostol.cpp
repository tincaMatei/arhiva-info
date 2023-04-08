/**
Apostol Ilie-Daniel - 100p O(NlogN)
**/
#include <bits/stdc++.h>

using ll = long long;
#define dbg(x) cerr << #x << " " << x << "\n"

const int MAX_N = 1e5;
const int INF = 1e9;
int C, N, T;
int PX[1 + MAX_N], PY[1 + MAX_N];

using Coord = std::pair <int, int>;
#define x first
#define y second


Coord moveUp(Coord now) {
    if (PY[now.y] + 1 > now.x && now.y == N)
        return {N, N};
    Coord answer = now;
    answer.x = PY[now.y] + 1;
    if (answer.x == N + 1)
        answer.x = 1;
    return answer;
}

Coord moveDown(Coord now) {
    if (PY[now.y] - 1 < now.x && now.y == N)
        return {N, N};
    Coord answer = now;
    answer.x = PY[now.y] - 1;
    if (answer.x == 0)
        answer.x = N;
    return answer;
}


Coord moveLeft(Coord now) {
    if (PX[now.x] + 1 > now.y && now.x == N)
        return {N, N};
    Coord answer = now;
    answer.y = PX[now.x] + 1;
    if (answer.y == N + 1)
        answer.y = 1;
    return answer;
}

Coord moveRight(Coord now) {
    if (PX[now.x] - 1 < now.y && now.x == N)
        return {N, N};
    Coord answer = now;
    answer.y = PX[now.x] - 1;
    if (answer.y == 0)
        answer.y = N;
    return answer;
}


int sumStr;

void solveCase1() {
    std::string moves;
    std::cin >> moves;
    sumStr += moves.size();
    assert(sumStr <= 1000000);
    Coord now = {1, 1};
    for (char mov : moves) {
        if (mov == 'U') {
            now = moveUp(now);
        }
        else if (mov == 'D') {
            now = moveDown(now);
        }
        else if (mov == 'L') {
            now = moveLeft(now);
        }
        else {
            now = moveRight(now);
        }
        if (now.x == N && now.y == N) {
            std::cout << "Won\n";
            return;
        }
    }
    std::cout << "Lost\n";
}

int minMoves[1 + 4 * MAX_N + 2];
std::queue <Coord> q;

void update(int from, int to, Coord coord) {
    if (minMoves[to] > minMoves[from] + 1) {
        minMoves[to] = minMoves[from] + 1;
        q.push(coord);
    }
}
void solveCase2() {
    std::map <std::pair <int, int>, int> nrm;
    nrm[{1, 1}];
    nrm[{N, N}];
    for (int i = 1; i <= N; i++) {
        if (PX[i] == 1)
            nrm[{i, N}];
        else
            nrm[{i, PX[i] - 1}];
        if (PX[i] == N)
            nrm[{i, 1}];
        else
            nrm[{i, PX[i] + 1}];
        if (i == 1)
            nrm[{N, PX[i]}];
        else
            nrm[{i - 1, PX[i]}];
        if (i == N)
            nrm[{1, PX[i]}];
        else
            nrm[{i + 1, PX[i]}];
    }
    int tag = 0;
    for (auto &x : nrm)
        x.second = ++tag;
    assert(tag <= 4 * MAX_N + 2);
    for (int i = 1; i <= tag; i++)
        minMoves[i] = INF;
    if (PX[1] != 1) {
        minMoves[nrm[{1, 1}]] = 0;
        q.push({1, 1});
    }

    while (q.size()) {
        Coord now = q.front();
        int tagNow = nrm[now];
        q.pop();
        /// alunecam in sus
        Coord nxtUp = moveUp(now);
        int tagUp = nrm[nxtUp];
        update(tagNow, tagUp, nxtUp);

        /// alunecam in jos
        Coord nxtDown = moveDown(now);
        int tagDown = nrm[nxtDown];
        update(tagNow, tagDown, nxtDown);

        /// alunecam in sus
        Coord nxtLeft = moveLeft(now);
        int tagLeft = nrm[nxtLeft];
        update(tagNow, tagLeft, nxtLeft);

        /// alunecam in dreapta
        Coord nxtRight = moveRight(now);
        int tagRight = nrm[nxtRight];
        update(tagNow, tagRight, nxtRight);
    }
    if (minMoves[nrm[{N, N}]] == INF) {
        std::cout << "-1\n";
    }
    else {
        std::cout << minMoves[nrm[{N, N}]] << "\n";
    }
}

int main() {
    freopen("arcade.in", "r", stdin);
    freopen("arcade.out", "w", stdout);
    std::cin >> C >> T;
    assert(1 <= T && T <= MAX_N / 2);
    int sumN = 0;
    while (T--) {
        std::cin >> N;
        sumN += N;
        assert(1 <= C && C <= 2);
        assert(1 <= N && N <= MAX_N);
        assert(1 <= sumN && sumN <= MAX_N);
        for (int i = 1; i <= N; i++) {
            std::cin >> PX[i];
            PY[PX[i]] = i;
            assert(1 <= PX[i] && PX[i] <= N);
        }
        assert(PX[1] != 1 && PX[N] != N);
        if (C == 1)
            solveCase1();
        else if (C == 2)
            solveCase2();
    }
    return 0;
}
