// stud. Bogdan Vlad-Mihai 
// Universitatea din București
// Soluție cu Principiul Includerii și Excluderii in O(2^N * M).
#include <bits/stdc++.h>

const int NMAX = 22;
const int SIGMA = 26;
const int BITS = 31;
const int MOD = 1e9 + 9;

int cnt[1 << NMAX], possible[1 << NMAX][NMAX];
int combi[NMAX + 1][NMAX + 1], bases[NMAX][NMAX];

int main() {
    assert(freopen("comun.in", "r", stdin));
    assert(freopen("comun.out", "w", stdout));

    int N, M, K; std::cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::string S; std::cin >> S;
            for (const char &c : S) {
                bases[i][j] |= (1 << (c - (int)'a'));
            }
        }
    }

    std::fill(possible[0], possible[0] + M, (1 << SIGMA) - 1);
    for (int mask = 1; mask < (1 << N); mask++) {
        int msb = BITS - __builtin_clz(mask);
        cnt[mask] = 1;
        for (int i = 0; i < M; i++) {
            possible[mask][i] = possible[mask ^ (1 << msb)][i] & bases[msb][i];
            cnt[mask] = (int64_t)cnt[mask] * __builtin_popcount(possible[mask][i]) % MOD;
        }
    }

    combi[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        combi[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            combi[i][j] = (combi[i - 1][j] + combi[i - 1][j - 1]) % MOD;
        }
    }

    int answer = 0;
    for (int mask = 1; mask < (1 << N); mask++) {
        int card = __builtin_popcount(mask);
        if (card >= K) {
            int add = (int64_t)combi[card - 1][card - K] * cnt[mask] % MOD;
            answer = ((int64_t)MOD + answer + add * ((card - K) % 2 == 1 ? -1 : 1)) % MOD;
        }
    }

    std::cout << answer << "\n";
    return 0;
}