#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1 << 20;

struct M {
	int val_st, nr_st, val_dr, nr_dr, optim, len, st, nr_benzi;

	M() : val_st(-12), nr_st(0), val_dr(-13), nr_dr(0), optim(0), len(0), st(1e9), nr_benzi(0) {}
	M(int x, int poz) : val_st(x), val_dr(x), nr_st(1), nr_dr(1), optim(1), len(1), st(poz), nr_benzi(1) {}

	M(const M& st, const M& dr)
		: val_st(st.val_st),
		nr_st(st.nr_st),
		val_dr(dr.val_dr),
		nr_dr(dr.nr_dr),
		optim(max(st.optim, dr.optim)),
		len(st.len + dr.len),
		st(min(st.st, dr.st)),
		nr_benzi(st.nr_benzi + dr.nr_benzi) {
		if (st.nr_st == st.len && st.val_st == dr.val_st) nr_st += dr.nr_st;
		if (dr.nr_dr == dr.len && dr.val_dr == st.val_dr) nr_dr += st.nr_dr;
		if (st.val_dr == dr.val_st) {
			optim = max(optim, st.nr_dr + dr.nr_st);
			--nr_benzi;
		}
	}

	M operator+(const M& dr) const { return this->len == 0 ? dr : dr.len == 0 ? *this : M{ *this, dr }; }

	M operator*(int x) const {
		if (x == 0)
			return M{};
		else if (x == 1)
			return *this;
		else {
			M ret = *this + *this;
			if (ret.optim == ret.len) ret.nr_st = ret.nr_dr = ret.optim = len * x;

			ret.len = len * x;
			int delta_benzi = ret.nr_benzi - nr_benzi;
			ret.nr_benzi = x * nr_benzi - (x - 1) * (val_st == val_dr);

			return ret;
		}
	}
};

struct K_info {
	int len, st;
	M sum;
	vector<M> pref_sum, suff_sum, rmq[20];

	K_info(int poz, vector<int> b) : len(b.size()), st(poz), sum({}), pref_sum(len + 1), suff_sum(len + 1) {
		for (int i = 1; i <= len; ++i) pref_sum[i] = pref_sum[i - 1] + M(b[i - 1], 0);
		for (int i = len - 1; i >= 0; --i) suff_sum[i] = M(b[i], 0) + suff_sum[i + 1];
		sum = suff_sum[0];

		for (int i = 0; i < 20; ++i) rmq[i].resize(len);

		for (int i = 0; i < len; ++i) rmq[0][i] = M(b[i], 0);
		for (int i = 1; i < 20; ++i)
			for (int j = 0, k = j + (1 << (i - 1)); k < len; ++j, ++k) rmq[i][j] = rmq[i - 1][j] + rmq[i - 1][k];
	}
};

struct K {
	const K_info* ki;

	K() : ki(nullptr) {}
	K(K_info* k) : ki(k) {}

	operator bool() const { return (bool)ki; }

	M operator*(const M& m) const {
		if (!ki) return m;

		int st = m.st - ki->st, dr = m.st + m.len - ki->st;
		M t =
			(st / ki->len == dr / ki->len)
			? ki->rmq[__builtin_ctz(m.len)][st % ki->len]
			: ki->suff_sum[st % ki->len] + ki->sum * (dr / ki->len - st / ki->len - 1) + ki->pref_sum[dr % ki->len];
		t.st = m.st;
		assert(m.len == t.len);
		assert(__builtin_popcount(m.len) == 1);
		return t;
	}

	K operator*(const K& k) const { return (bool)(*this) ? *this : k; }
};

M buf[2 * maxn];
K lazy[maxn];

void recalc(int i) { buf[i] = lazy[i] * (buf[2 * i] + buf[2 * i + 1]); }

void ap(int i, const K& k) {
	if (i < maxn) lazy[i] = k * lazy[i];
	buf[i] = k * buf[i];
}

void prop(int i) {
	if (lazy[i]) {
		ap(2 * i, lazy[i]);
		ap(2 * i + 1, lazy[i]);
		lazy[i] = K{};
	}
}

void up(int x) {
	while (x /= 2) recalc(x);
}

void down(int x) {
	for (int i = 22; i > 0; --i)
		if (x >> i) prop(x >> i);
}

M query(int st, int dr) {
	M ret_st = {}, ret_dr = {};
	down(st += maxn);
	down((dr += maxn) - 1);
	for (; st < dr; st /= 2, dr /= 2) {
		if (st % 2) ret_st = ret_st + buf[st++];
		if (dr % 2) ret_dr = buf[--dr] + ret_dr;
	}
	return ret_st + ret_dr;
}

void update(int st, int dr, const K& k) {
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

pair<int, int> solve(int l, int r) {
	auto t = query(l, r);
	return make_pair(max(1, t.nr_benzi - (t.val_st == t.val_dr ? 1 : 0)), min(t.len, (t + t).optim));
}

pair<int, int> brut_solve(int l, int r) {
	vector<int> v;
	for (int i = l; i < r; ++i) v.push_back(query(i, i + 1).val_st);
	if (v.front() == v.back()) {
		int i = 0;
		while (i + 1 < v.size() && v[i] == v[i + 1]) ++i;
		rotate(begin(v), begin(v) + i + 1, end(v));
	}

	int nr_benzi = v.size();
	for (int i = 0; i + 1 < v.size(); ++i)
		if (v[i] == v[i + 1]) nr_benzi--;

	int ret = 1, curr = 1;
	for (int i = 1; i < v.size(); ++i) {
		curr = (v[i] == v[i - 1] ? curr + 1 : 0);
		ret = max(ret, curr);
	}
	return make_pair(nr_benzi, ret);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;

	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		buf[maxn + i] = M(x, i);
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
			cout << t.first << ' ' << t.second << endl;
		}
		else {
			cin >> m;
			vector<int> b(m);
			for (auto& x : b) cin >> x;
			update(l, r, K(new K_info(l, b)));
		}
	}

	for (int i = 0; i < n; ++i) cout << query(i, i + 1).val_st << ' ';
	cout << endl;
	return 0;
}
