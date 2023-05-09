// O(r-l), O(r-l) per query

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    auto Query = [&](int l, int r) {
        int nr = 0, cur = -1, curlen = 0, best = 0;
        for (int i = l;i <= r;++i)
            if (a[i] != cur) {
                ++nr;
                best = max(best, curlen);
                curlen = 1;
                cur = a[i];
            }
            else
                ++curlen;
        if (nr != 1 && a[l] == a[r]) {
            --nr;
            for (int i = l;i <= r && a[i] == cur;++i)
                ++curlen;
            best = max(best, curlen);
        }
        else
            best = max(best, curlen);
        return make_pair(nr, best);
    };
    for (int i = 1;i <= n;++i)
        cin >> a[i];
    auto ans = Query(1, n);
    cout << ans.first << ' ' << ans.second << '\n';
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            auto ans = Query(l, r);
            cout << ans.first << ' ' << ans.second << '\n';
        }
        else {
            int m;
            cin >> m;
            vector<int> v(m);
            for (auto& x : v)
                cin >> x;
            for (int i = l, cur = 0;i <= r;++i, cur = (cur + 1) % m)
                a[i] = v[cur];
        }
    }
    for (int i = 1;i <= n;++i)
        cout << a[i] << ' ';
}