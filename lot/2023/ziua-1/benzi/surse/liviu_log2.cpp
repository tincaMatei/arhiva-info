// O(n) build st
// O(M) build ds (st)
// O(1), O(log n log M) per query

#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> patterns = { {} };

struct node {
	int nr = 0;
	// count, colour
	pair<int, int> pref, suf, best;
	// id, offset
	pair<int, int> lazy;
	constexpr node() {}
	node(int col) : nr(1), pref(1, col), suf(1, col), best(1, col) {}
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

vector<vector<node>> pref = { {} };

struct ds {
	int n;
	vector<node> st;
	void Build(const vector<int>& a, int node, int left, int right) {
		if (left == right) {
			st[node] = ::node(a[left - 1]);
			return;
		}
		int m = (left + right) / 2;
		Build(a, 2 * node, left, m), Build(a, 2 * node + 1, m + 1, right);
		st[node] = node::combine(st[2 * node], st[2 * node + 1]);
	}
	ds(const vector<int>& a) {
		n = a.size();
		st.resize(4 * n);
		Build(a, 1, 1, n);
	}
	node Query(int posleft, int posright) {
		return Query(posleft + 1, posright + 1, 1, 1, n);
	}
	node Query(int posleft, int posright, int node, int left, int right) {
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
};

vector<ds> pats;

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
			ans = node::combine(ans, combine_times(pref[id].back(), cnt));
		int rem = size % len;
		if (rem)
			ans = node::combine(ans, pref[id][rem - 1]);
	}
	st[node] = ans;
	if (left != right) {
		st[2 * node].lazy = st[2 * node + 1].lazy = { id, pre };
		int m = (left + right) / 2;
		(st[2 * node + 1].lazy.second += m + 1 - left) %= len;
	}
	st[node].lazy.first = 0;
}

node Query(int posleft, int posright, int node = 1, int left = 1, int right = n) {
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

void Update(int posleft, int posright, int id, int node = 1, int left = 1, int right = n) {
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
			patterns.emplace_back(), pref.emplace_back();
			int m;
			cin >> m;
			patterns.back().resize(m), pref.back().resize(m);
			for (auto& x : patterns.back())
				cin >> x;
			node cur(patterns.back()[0]);
			pref.back()[0] = cur;
			for (int i = 1; i < m; ++i) {
				cur = node::combine(cur, patterns.back()[i]);
				pref.back()[i] = cur;
			}
			pats.emplace_back(patterns.back());
			Update(l, r, patterns.size() - 1);
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << Query(i, i).best.second << ' ';
}