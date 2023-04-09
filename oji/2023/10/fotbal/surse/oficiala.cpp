// Solution stud. Vlad-Mihai Bogdan
// Universitatea din Bucuresti
#include <bits/stdc++.h>
using namespace std;

ifstream in("fotbal.in");
ofstream out("fotbal.out");

const int M = 1e9 + 9;

struct Event {
    int pos;
    bool start, f;
    Event(int _pos, bool _start, bool _f) : pos(_pos), start(_start), f(_f) {}
    bool operator < (const Event &other) const {
        return pos < other.pos || (pos == other.pos && start < other.start);
    }
};

void sub(int &N, int value) {
    N -= value;
    if (N < 0) {
        N += M;
    }
}

void add(int &N, int value) {
    N += value;
    if (N >= M) {
        N -= M;
    }
}

int lgpow(int A, int B) {
    int answer = 1;
    while (B > 0) {
        if (B % 2 == 1) {
            answer = (int64_t)answer * A % M;
        }
        A = (int64_t)A * A % M;
        B /= 2;
    }
    return answer;
}

pair<vector<int>, vector<int>> init(int N) {
    vector<int> fact(N + 1, 1);
    for (int i = 2; i <= N; i++) {
        fact[i] = (int64_t)fact[i - 1] * i % M;
    }
    vector<int> inverse(N + 1);
    inverse.back() = lgpow(fact.back(), M - 2);
    for (int i = N - 1; i >= 0; i--) {
        inverse[i] = (int64_t)inverse[i + 1] * (i + 1) % M;
    }
    return make_pair(fact, inverse);
}

int main() {
    int N, K; in >> N >> K;
    vector<Event> events;
    for (int i = 0; i < N; i++) {
        int l, r; in >> l >> r;
        bool f; in >> f;
        events.push_back(Event(l, true, f));
        events.push_back(Event(r + 1, false, f));
    }
    sort(events.begin(), events.end());
    vector<int> factorial, inverse;
    tie(factorial, inverse) = init(N);
    auto C = [&](int N, int K) -> int {
        if (N < K) {
            return 0;
        }
        return (int64_t)factorial[N] * inverse[K] % M * inverse[N - K] % M;
    };
    int answer = 0, activeLefties = 0, active = 0;
    for (const auto &event : events) {
        if (event.start) {
            add(answer, C(active, K - 1));
            if (!event.f) {
                sub(answer, C(active - activeLefties, K - 1));
            } else {
                sub(answer, C(activeLefties, K - 1));
            }
        }
        int mlt = (event.start ? 1 : -1);
        active += mlt;
        activeLefties += event.f * mlt;
    }
    out << answer << "\n";
    return 0;
}