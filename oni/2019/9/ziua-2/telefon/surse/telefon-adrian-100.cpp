#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#define int int64_t

using namespace std;

int32_t main() {
    ifstream cin("telefon.in");
    ofstream cout("telefon.out");

    int N, B; cin >> N >> B;

    vector<int> X(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
    }

    for (int i = N - 1; i > 0; --i)
        X[i] -= X[i - 1];
    X.erase(X.begin());
    --N;

    sort(X.begin(), X.end());

    vector<int> partial(X.size());
    for (int i = 0; i < int(X.size()); ++i) {
        partial[i] += X[i];
        if (i > 0)
            partial[i] += partial[i - 1];
    }

    int answer = numeric_limits<int>::max();

    for (int i = 0; i < int(X.size()); ++i) {
        // this is max
        int can_take = B / X[i];
        int need = partial.back() - partial[i];
        if (can_take <= i)
            need += partial[i - can_take];
        answer = min(answer, need);
    }

    cout << answer << " ";

    answer = numeric_limits<int>::max();
    N = X.size();
    for (int cover = N + 1, end = -1, magic = 0; cover > 0; --cover) {
        int max_cover = B / cover;
        // 3 ways
        // we cover cover of already existant values
        // we cover cover - 1 of already existent values + some part of the biggest
        // we cover cover - 2 of already + the biggest <= 2 * max_cover 

        while (end + 1 < N && X[end + 1] <= max_cover) {
            ++end;
        }

        if (end == -1)
            continue;

        while (magic + 1 < N && X[magic + 1] <= 2 * max_cover)
            ++magic;

        // ignore Dorel
        int now = partial[N - 1] - partial[end];
        if (end - cover >= 0)
            now += partial[end - cover];

        answer = min(answer, now);

        // Dorel once
        if (cover > 0) {
            now = partial[N - 1] - partial[end];
            if (end - (cover - 1) >= 0)
                now += partial[end - (cover - 1)];
            if (end < N - 1)
                now -= min(max_cover, X[N - 1]);
            answer = min(answer, now);
        }

        // Dorel twice
        if (cover > 1) {
            now = partial[N - 1] - partial[end];
            if (end - (cover - 2) >= 0)
                now += partial[end - (cover - 2)];
            if (end < magic)
                now -= X[magic];
            answer = min(answer, now);
        }
    }

    cout << answer << "\n";
}