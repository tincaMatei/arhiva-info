// stud. Bogdan Vlad-Mihai 
// Universitatea din București
// Soluție cu programare dinamică cu timp O(T) și memorie O(min(N, M))
#include <bits/stdc++.h>

const int MOD = 1e9 + 9;

int main() {
    assert(freopen("matrice.in", "r", stdin));
    assert(freopen("matrice.out", "w", stdout));

    int N, M, T; std::cin >> N >> M >> T;

    if (N < M) {
        std::swap(N, M);
    }

    int answer = 0;
    if (M > 1) {
        std::deque<int> dp(M - 1, 0);
        int count = 0, totalCount = 0;
        for (int i = M; i <= T; i++) {
            int add = ((i - (M - 1)) % (N - 1) == 0 && i - (M - 1) > 0) + dp.back();
            if (add >= MOD) {
                add -= MOD;
            }
            dp.push_front(add);

            count += dp.front();
            if (count >= MOD) {
                count -= MOD;
            }
            totalCount += count;
            if (totalCount >= MOD) {
                totalCount -= MOD;
            }
            if ((T - i) % ((N - 1) * (M - 1)) == 0) {
                answer += totalCount;
                if (answer >= MOD) {
                    answer -= MOD;
                }
            }
            
            dp.pop_back();
        }
    } else if (N > 1) {
        for (int f = 0; f <= T; f++) {
            answer += (T - f) / (N - 1);
            if (answer >= MOD) {
                answer -= MOD;
            }
        }
    } else {
        answer = T + 1;
    }

    std::cout << answer << "\n";

    return 0;
}