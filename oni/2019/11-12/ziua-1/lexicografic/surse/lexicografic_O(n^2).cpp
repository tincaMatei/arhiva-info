#include <bits/stdc++.h>

using namespace std;

using lint = long long int;
const int NMAX = 250000;
// const int KMAX = ?;

void run_test() {
    // Read and asserts
    int N;
    cin >> N;
    lint K;
    cin >> K;
    assert(1 <= N && N <= NMAX);
    // TODO: Add assert for K
    vector <int> v(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i];
    }

    // Run greedy
    for (int i = 0; i < N; ++i) {
        const int limit = min(static_cast <lint>(N - 1), i + K);
        int minimum = v[i], pos = i;
        for (int j = i + 1; j <= limit; ++j) {
            if (v[j] < minimum) {
                minimum = v[j];
                pos = j;
            }
        }
        K -= (pos - i);
        while (pos > i) {
            v[pos] = v[pos - 1];
            --pos;
        }
        v[i] = minimum;
        /*for (int j = 0; j < N; ++j) {
            cerr << v[j] << ' ';
        }
        cerr << endl;*/
    }

    // Print answer
    for (int i = 0; i < static_cast <int>(v.size()); ++i) {
        cout << v[i] << " \n"[i + 1 == v.size()];
    }
}

int main() {
    freopen("lexicografic.in", "r", stdin);
    freopen("lexicografic.out", "w", stdout);
    int T = 0;
    cin >> T;
    while (T--) {
        run_test();
    }
    return 0;    
}
