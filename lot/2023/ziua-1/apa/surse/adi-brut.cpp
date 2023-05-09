#include <bits/stdc++.h>

#define N_MAX 100000

using namespace std;

int N, M, Q;
vector<int> G[N_MAX + 5];
int T[N_MAX + 5];
int lev[N_MAX + 5];
int cnt[N_MAX + 5];

void DFS(int node) {
  cnt[node] = 1;
  for (auto it : G[node]) {
    if (lev[it] == 0) {
      lev[it] = 1 + lev[node];
      T[it] = node;
      DFS(it);
      cnt[node] += cnt[it];
    }
  }
}

long long query_brut(int a, int b, int h) {
  vector<int> first, second;
  while (a != b) {
    if (lev[a] < lev[b]) {
      second.push_back(b);
      b = T[b];
    } else {
      first.push_back(a);
      a = T[a];
    }
  }

  long long ans = 0;
  for (int i = 0; i < first.size(); i++) {
    int sub = (i == 0 ? 0 : cnt[first[i - 1]]);
    ans += 1ll * max(h - i, 0) * (cnt[first[i]] - sub);
    // cerr << first[i] << " " << (h - i) << " " << cnt[first[i]] - sub << "\n";
  }

  int coef = N;
  if (!first.empty()) {
    coef -= cnt[first.back()];
  }
  if (!second.empty()) {
    coef -= cnt[second.back()];
  }
  ans = ans + 1ll * coef * max(h - (int)first.size(), 0);
  // cerr << a << " " << coef << " " << (h - first.size()) << "\n";

  for (int i = second.size() - 1; i >= 0; i--) {
    int sub = (i == 0 ? 0 : cnt[second[i - 1]]);
    int coef = max(h - (int)first.size() - ((int)second.size() - 1 - i) - 1, 0);
    ans += 1ll * coef * (cnt[second[i]] - sub);
    // cerr << second[i] << " " << coef << " " << cnt[second[i]] - sub << "\n";
  }

  return ans;
}

int main() {
  cin >> N >> Q;
  for (int i = 1; i < N; i++) {
    int x, y;
    cin >> x >> y;
    G[x].push_back(y);
    G[y].push_back(x);
  }

  lev[1] = 1;
  DFS(1);
  while (Q--) {
    int a, b, h;
    cin >> a >> b >> h;
    cout << query_brut(a, b, h) << "\n";
  }
  return 0;
}