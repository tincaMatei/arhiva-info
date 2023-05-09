#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1 << 18;

struct M {
    int val_st = -12, nr_st = 0, val_dr = -13, nr_dr = 0, optim = 0, len = 0, st = 1e9, nr_benzi = 0;
    M() {}
    M(int a, int b, int c, int d, int e, int f, int g, int h)
        : val_st(a), nr_st(b), val_dr(c), nr_dr(d), optim(e), len(f), st(g), nr_benzi(h) {}
};

static M mk_M(int x, int poz) { return M{x, 1, x, 1, 1, 1, poz, 1}; }

static M operator+(const M &st, const M &dr) {
    if (st.len == 0) return dr;
    if (dr.len == 0) return st;
    M ret{st.val_st,
          st.nr_st,
          dr.val_dr,
          dr.nr_dr,
          max(st.optim, dr.optim),
          st.len + dr.len,
          min(st.st, dr.st),
          st.nr_benzi + dr.nr_benzi};
    if (st.nr_st == st.len && st.val_st == dr.val_st) ret.nr_st += dr.nr_st;
    if (dr.nr_dr == dr.len && dr.val_dr == st.val_dr) ret.nr_dr += st.nr_dr;
    if (st.val_dr == dr.val_st) {
        ret.optim = max(ret.optim, st.nr_dr + dr.nr_st);
        --ret.nr_benzi;
    }

    return ret;
}

static M operator*(const M &st, int x) {
    if (x == 0)
        return M{};
    else if (x == 1)
        return st;
    else {
        M ret = st + st;
        if (ret.optim == ret.len) ret.nr_st = ret.nr_dr = ret.optim = st.len * x;

        ret.len = st.len * x;
        int delta_benzi = ret.nr_benzi - st.nr_benzi;
        ret.nr_benzi += (x - 2) * delta_benzi;

        return ret;
    }
}

struct K_info {
    int len, st, N;
    M sum;
    vector<M> aint;

    K_info() {}
} k_info_buf[maxn];
int curr_k_info_buf_poz = 1;

static void mk_k_info(K_info &me, int poz, vector<int> b) {
    me.len = b.size();
    me.N = 1 << (int)ceil(log2(me.len));
    me.st = poz;
    me.aint.resize(me.N);
    for (int i = me.N; i < me.N + me.len; ++i) me.aint[i] = mk_M(b[i - me.len], 0);
    for (int i = me.N - 1; i > 0; --i) me.aint[i] = me.aint[2 * i] + me.aint[2 * i + 1];

    me.sum = M{};
    for (auto x : b) me.sum = me.sum + mk_M(x, 0);
}

static M k_info_query(K_info &me, int st, int dr) {
    M ret_st = {}, ret_dr = {};
    for (st += me.N, dr += me.N; st < dr; st /= 2, dr /= 2) {
        if (st % 2) ret_st = (ret_st + me.aint[st++]);
        if (dr % 2) ret_dr = (me.aint[--dr] + ret_dr);
    }
    return ret_st + ret_dr;
}

struct K {
    int i;
};

static M operator*(const K &k, const M &m) {
    if (!k.i) return m;

    int st = m.st - k_info_buf[k.i].st, dr = m.st + m.len - k_info_buf[k.i].st;
    M t = (st / k_info_buf[k.i].len == dr / k_info_buf[k.i].len)
              ? k_info_query(k_info_buf[k.i], st % k_info_buf[k.i].len, st % k_info_buf[k.i].len + m.len)
              : k_info_query(k_info_buf[k.i], st % k_info_buf[k.i].len, k_info_buf[k.i].len) +
                    k_info_buf[k.i].sum * (dr / k_info_buf[k.i].len - st / k_info_buf[k.i].len - 1) +
                    k_info_query(k_info_buf[k.i], 0, dr % k_info_buf[k.i].len);
    t.st = m.st;
    return t;
}

static K operator*(const K &k0, const K &k) { return (bool)(k0.i) ? k0 : k; }

M buf[2 * maxn] = {};
K lazy[maxn] = {};

static void recalc(int i) { buf[i] = lazy[i] * (buf[2 * i] + buf[2 * i + 1]); }

static void ap(int i, const K &k) {
    if (i < maxn) lazy[i] = k * lazy[i];
    buf[i] = k * buf[i];
}

static void prop(int i) {
    if (lazy[i].i) {
        ap(2 * i, lazy[i]);
        ap(2 * i + 1, lazy[i]);
        lazy[i] = K{};
    }
}

static void up(int x) {
    while (x /= 2) recalc(x);
}

static void down(int x) {
    for (int i = 18; i > 0; --i)
        if (x >> i) prop(x >> i);
}

static void prop_all() {
    for (int i = 1; i < maxn; ++i) prop(i);
}

static M query(int st, int dr) {
    M ret_st = {}, ret_dr = {};
    down(st += maxn);
    down((dr += maxn) - 1);
    for (; st < dr; st /= 2, dr /= 2) {
        if (st % 2) ret_st = ret_st + buf[st++];
        if (dr % 2) ret_dr = buf[--dr] + ret_dr;
    }
    return ret_st + ret_dr;
}

static void update(int st, int dr, const K &k) {
    const int st0 = st, dr0 = dr;
    down(st += maxn);
    down((dr += maxn) - 1);
    for (; st < dr; st /= 2, dr /= 2) {
        if (st % 2) ap(st++, k);
        if (dr % 2) ap(--dr, k);
    }
    up(st0 + maxn);
    up(dr0 + maxn - 1);
}

static pair<int, int> solve(int l, int r) {
    auto t = query(l, r);
    return make_pair(max(1, t.nr_benzi - (t.val_st == t.val_dr ? 1 : 0)), min(t.len, (t + t).optim));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        buf[maxn + i] = mk_M(x, i);
    }

    for (int i = maxn - 1; i > 0; --i) recalc(i);

    auto t = solve(0, n);
    cout << t.first << ' ' << t.second << '\n';

    while (q--) {
        int t, l, r, m;
        cin >> t >> l >> r;
        --l;

        if (t == 1) {
            auto t = solve(l, r);
            cout << t.first << ' ' << t.second << '\n';
        } else {
            cin >> m;
            vector<int> b(m);
            for (auto &x : b) cin >> x;
            mk_k_info(k_info_buf[curr_k_info_buf_poz], l, b);
            update(l, r, K{curr_k_info_buf_poz++});
        }
    }

    prop_all();
    for (int i = 0; i < n; ++i) cout << buf[i + maxn].val_st << ' ';

    return 0;
}
