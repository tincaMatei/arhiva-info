// brute, O(n*n!)
#pragma GCC optimize("O2")
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a)
        cin >> x;
    auto Solve = [&](int k) {
        sort(a.begin(), a.end());
        int cnt = 0;
        do {
            int good = 1;
            for (int i = 1;i < n;++i)
                if ((a[i] - a[i - 1]) % k == 0) {
                    good = 0;
                    break;
                }
            cnt += good;
        } while (next_permutation(a.begin(), a.end()));
        return cnt;
    };
    cout << Solve(k);
}
