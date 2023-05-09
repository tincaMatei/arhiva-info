// O(n(n-k))
#include <bits/stdc++.h>
using namespace std;

// std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// int rand(int x, int y) { return std::uniform_int_distribution<int>(x, y)(rng); };

int main() {
    const int mod = 1e9 + 7;
    int n, k;
    cin >> n >> k;
    // n = 2500, k = 2 * 3 * 5 * 7 * 11 * 13;
    vector<int> a(n), fact(n + 1);
    map<int, int> mp;
    for (auto& x : a) {
        // x = rand(1, 1E9);
        cin >> x;
        ++mp[x];
    }
    vector<vector<int>> comb(n + 1, vector<int>(n + 1));
    comb[0][0] = fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1LL * i * fact[i - 1] % mod;
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }
    }
    int coef = 1;
    for (auto& [x, y] : mp)
        coef = 1LL * coef * fact[y] % mod;
    auto pow = [&](int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1)
                ans = (1LL * ans * b) % mod;
            b = (1LL * b * b) % mod, e >>= 1;
        }
        return ans;
    };
    coef = pow(coef, mod - 2);
    auto Solve = [&](int k) {
        vector<int> initcnt(k), cnt;
        for (auto& x : a)
            ++initcnt[x % k];
        for (auto x : initcnt)
            if (x)
                cnt.emplace_back(x);
        int m = cnt.size(), s = 0;
        vector<vector<int>> dp(2, vector<int>(n + 1));
        dp[1][0] = 1;
        for (int i = 0; i < m; ++i) {
            fill(dp[i & 1].begin() + max(0, i - 1), dp[i & 1].begin() + s + 1, 0);
            for (int j = 1; j <= cnt[i]; ++j)
                for (int k = i; k <= s; ++k)              // splitting cnt[i] in j groups (ordered; stars and bars) | choosing where to place the new j groups (already ordered) 
                    dp[i & 1][j + k] = (dp[i & 1][j + k] + 1LL * dp[(i & 1) ^ 1][k] * comb[cnt[i] - 1][j - 1] % mod * comb[j + k][j]) % mod;
            s += cnt[i];
        }
        int ans = 0;
        for (int i = n, sgn = 1; i; --i, sgn *= -1) {
            ans += sgn * dp[(m & 1) ^ 1][i];
            if (ans < 0)
                ans += mod;
            else if (ans >= mod)
                ans -= mod;
        }
        // up to this point elements are only ordered according to equivalence classes modulo k
        for (auto x : cnt)
            ans = 1LL * ans * fact[x] % mod;
        ans = 1LL * ans * coef % mod;
        return ans;
    };
    cout << Solve(k);
}
