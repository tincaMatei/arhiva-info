// O(n) build st
// O(1), O(r-l) per query

#include <bits/stdc++.h>

using namespace std;

int n;

struct node {
    int nr = 0;
    // count, colour
    pair<int, int> pref, suf, best;
    // id, offset
    pair<int, int> lazy;
    constexpr node() {}
    node(int col): nr(1), pref(1, col), suf(1, col), best(1, col) {}
    node static combine(const node& a, const node& b) {
        if (a.nr == 0)
            return b;
        if (b.nr == 0)
            return a;
        node ans;
        ans.nr = a.nr + b.nr - (a.suf.second == b.pref.second);
        ans.pref = a.pref;
        if (a.nr == 1 && a.pref.second == b.pref.second)
            ans.pref.first += b.pref.first;
        ans.suf = b.suf;
        if (b.nr == 1 && b.suf.second == a.suf.second)
            ans.suf.first += a.suf.first;
        ans.best = max(a.best, b.best);
        if (a.suf.second == b.pref.second)
            ans.best = max(ans.best, { a.suf.first + b.pref.first,a.suf.second });
        return ans;
    }
    pair<int, int> get_answer() {
        int nr = this->nr, cntmax = best.first;
        if (nr != 1 && pref.second == suf.second)
            --nr, cntmax = max(cntmax, pref.first + suf.first);
        return { nr,cntmax };
    }
} st[1 << 19];

void Build(int node = 1, int left = 1, int right = n) {
    if (left == right) {
        int col;
        cin >> col;
        st[node] = ::node(col);
        return;
    }
    int m = (left + right) / 2;
    Build(2 * node, left, m), Build(2 * node + 1, m + 1, right);
    st[node] = node::combine(st[2 * node], st[2 * node + 1]);
}

node Query(int posleft, int posright, int node = 1, int left = 1, int right = n) {
    if (posleft <= left && right <= posright)
        return st[node];
    int m = (left + right) / 2;
    ::node l, r;
    if (posleft <= m)
        l = Query(posleft, posright, 2 * node, left, m);
    if (posright > m)
        r = Query(posleft, posright, 2 * node + 1, m + 1, right);
    return node::combine(l, r);
}

void Update(int pos, int col, int node = 1, int left = 1, int right = n) {
    if (left == right) {
        st[node] = ::node(col);
        return;
    }
    int m = (left + right) / 2;
    if (pos <= m)
        Update(pos, col, 2 * node, left, m);
    else
        Update(pos, col, 2 * node + 1, m + 1, right);
    st[node] = node::combine(st[2 * node], st[2 * node + 1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> n >> q;
    Build();
    auto ans = st[1].get_answer();
    cout << ans.first << ' ' << ans.second << '\n';
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            auto ans = Query(l, r).get_answer();
            cout << ans.first << ' ' << ans.second << '\n';
        }
        else {
            int m;
            cin >> m;
            vector<int> v(m);
            for (auto& x : v)
                cin >> x;
            for (int i = l, cur = 0;i <= r;++i, cur = (cur + 1) % m)
                Update(i, v[cur]);
        }
    }
    for (int i = 1;i <= n;++i)
        cout << Query(i, i).best.second << ' ';
}