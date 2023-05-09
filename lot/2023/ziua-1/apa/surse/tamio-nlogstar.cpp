#include <iostream>
#include <vector>

using namespace std;

constexpr long long mod = 1e9 + 7, maxn = 3e5 + 10, maxk = 20;

int tt[maxn][maxk] = {}, adanc[maxn], sz[maxn], sp_sz[maxn], n, q;
vector<int> fii[maxn] = {};

void dfs(int curr) {
    sz[curr] = 1;
    for (auto next : fii[curr]) {
        fii[next].erase(find(begin(fii[next]), end(fii[next]), curr));
        tt[next][0] = curr;
        for (int j = 1; j < maxk; ++j) tt[next][j] = tt[tt[next][j - 1]][j - 1];
        adanc[next] = adanc[curr] + 1;
        dfs(next);
        sz[curr] += sz[next];
    }
}

void dfs2(int curr) {
    sp_sz[curr] += sz[curr];
    for (auto next : fii[curr]) {
        sp_sz[next] += sp_sz[curr];
        dfs2(next);
    }
}

int level_ancestor(int x, int lvl) {
    for (int i = maxk - 1; i >= 0; --i) {
        if (adanc[x] - (1 << i) >= lvl) {
            x = tt[x][i];
        }
    }
    assert(adanc[x] == lvl);
    return x;
}

int lca(int x, int y) {
    if (adanc[x] > adanc[y]) swap(x, y);
    y = level_ancestor(y, adanc[x]);
    assert(adanc[x] == adanc[y]);
    if (x == y) return x;

    for (int i = maxk - 1; i >= 0; --i)
        if (tt[x][i] != tt[y][i]) x = tt[x][i], y = tt[y][i];
    assert(tt[x][0] == tt[y][0]);
    return tt[x][0];
}

long long solve_query(int x, int y, int h) {
    int l = lca(x, y);
    if (adanc[x] + adanc[y] - 2 * adanc[l] > h) {
        if (adanc[x] - adanc[l] >= h) {
            y = level_ancestor(x, adanc[x] - h);
        } else {
            y = level_ancestor(y, adanc[y] - (adanc[x] + adanc[y] - 2 * adanc[l] - h));
        }
    }

    return sp_sz[x] - sp_sz[y] + (long long)(h - adanc[x] + adanc[lca(x, y)]) * n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 0, x, y; i < n - 1; ++i) {
        cin >> x >> y;
        fii[x].push_back(y);
        fii[y].push_back(x);
    }

    dfs(1);
    dfs2(1);

    while (q--) {
        int x, y, h;
        cin >> x >> y >> h;
        cout << solve_query(x, y, h) << '\n';
    }
}
