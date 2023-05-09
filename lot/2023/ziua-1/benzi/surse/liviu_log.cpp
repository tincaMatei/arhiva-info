// O(n) build st
// O(M log M) build ds
// O(1), O(log n) per query

#include <bits/stdc++.h>

using namespace std;

int n, N;
vector<vector<int>> patterns = { {} };

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

class ds {
public:
	ds(const vector<int>& temp):m(temp.size()) {
		for (auto x : temp)
			ans = node::combine(ans, ::node(x));
		pre.resize(m), pref.resize(m), suf.resize(m);
		for (int i = 0; i < m; ++i)
			pre[i][0] = ::node(temp[i]);
		pref[0] = ::node(temp[0]);
		for (int i = 1;i < m;++i)
			pref[i] = node::combine(pref[i - 1], ::node(temp[i]));
		suf[m - 1] = ::node(temp[m - 1]);
		for (int i = m - 2;~i;--i)
			suf[i] = node::combine(::node(temp[i]), suf[i + 1]);
		int lg = 31 - __builtin_clz(m);
		for (int i = 1; i <= lg; ++i)
			for (int j = 0; j < m; ++j)
				if (j + (1 << i) <= m)
					pre[j][i] = node::combine(pre[j][i - 1], pre[j + (1 << (i - 1))][i - 1]);
	}
	node Query(int l, int r) const {
		if (r == m - 1)
			return suf[l];
		if (l == 0)
			return pref[r];
		int cnt = 31 - __builtin_clz(r - l + 1);
		return pre[l][cnt];
	}
	node QueryAll() const {
		return suf[0];
	}
private:
	int m;
	node ans;
	vector<array<node, 18>> pre;
	vector<node> pref, suf;
};

vector<ds> pats;

void Build(int node = 1, int left = 1, int right = N) {
	if (left == right) {
		if (left <= n) {
			int col;
			cin >> col;
			st[node] = ::node(col);
		}
		return;
	}
	int m = (left + right) / 2;
	Build(2 * node, left, m), Build(2 * node + 1, m + 1, right);
	st[node] = node::combine(st[2 * node], st[2 * node + 1]);
}

node combine_times(const node& a, int n) {
	if (n == 1)
		return a;
	node ans;
	ans.nr = a.nr * n - (a.suf.second == a.pref.second) * (n - 1);
	ans.pref = a.pref;
	ans.suf = a.suf;
	ans.best = a.best;
	if (a.nr == 1)
		ans.pref.first = ans.suf.first = ans.best.first = n * a.pref.first;
	else
		if (a.suf.second == a.pref.second)
			ans.best = max(ans.best, { a.suf.first + a.pref.first,a.suf.second });
	return ans;
};

void Propagate(int node, int left, int right) {
	if (st[node].lazy.first == 0)
		return;
	int id = st[node].lazy.first, size = right - left + 1, len = patterns[id].size();
	int pre = st[node].lazy.second;
	::node ans = pats[id].Query(pre, min(len, pre + size) - 1);
	if (pre + size - 1 >= len) {
		size -= len - pre;
		int cnt = size / len;
		if (cnt)
			ans = node::combine(ans, combine_times(pats[id].QueryAll(), cnt));
		int rem = size % len;
		if (rem)
			ans = node::combine(ans, pats[id].Query(0, rem - 1));
	}
	st[node] = ans;
	if (left != right) {
		st[2 * node].lazy = st[2 * node + 1].lazy = { id, pre };
		int m = (left + right) / 2;
		(st[2 * node + 1].lazy.second += m + 1 - left) %= len;
	}
	st[node].lazy.first = 0;
}

node Query(int posleft, int posright, int node = 1, int left = 1, int right = N) {
	Propagate(node, left, right);
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

void Update(int posleft, int posright, int id, int node = 1, int left = 1, int right = N) {
	if (posleft <= left && right <= posright) {
		st[node].lazy = { id, (left - posleft) % patterns[id].size() };
		Propagate(node, left, right);
		return;
	}
	Propagate(node, left, right);
	int m = (left + right) / 2;
	if (posleft <= m)
		Update(posleft, posright, id, 2 * node, left, m), Propagate(2 * node + 1, m + 1, right);
	if (posright > m)
		Update(posleft, posright, id, 2 * node + 1, m + 1, right), Propagate(2 * node, left, m);
	st[node] = node::combine(st[2 * node], st[2 * node + 1]);
}

int main() {
	pats.emplace_back(vector<int>{1});
	cin.tie(0)->sync_with_stdio(0);
	int q;
	cin >> n >> q;
	N = 1 << (int)ceil(log2(n));
	Build();
	auto [nr, max] = st[1].get_answer();
	cout << nr << ' ' << max << '\n';
	while (q--) {
		int t, l, r;
		cin >> t >> l >> r;
		if (t == 1) {
			auto [nr, max] = Query(l, r).get_answer();
			cout << nr << ' ' << max << '\n';
		}
		else {
			patterns.emplace_back();
			int m;
			cin >> m;
			patterns.back().resize(m);
			for (auto& x : patterns.back())
				cin >> x;
			pats.emplace_back(patterns.back());
			Update(l, r, patterns.size() - 1);
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << Query(i, i).best.second << ' ';
}