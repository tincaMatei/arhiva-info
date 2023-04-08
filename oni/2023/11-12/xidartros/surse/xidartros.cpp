#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve_test() {
  int N, B, K;
  scanf("%d%d%d", &N, &B, &K);
  vector<int> prm(N + 1, 0), pos(N + 1, 0);
  vector<ll> ans(N + 1, 0);
  for (int i = 1; i <= N; i++)
    prm[i] = i;
  ll b = 1;
  bool ok = true;
  for (int i = 0; i < K; i++) {
    for (int j = 1; j <= N; j++)
      pos[prm[j]] = j;
    for (int j = 1; j <= N; j++)
      scanf("%d", &prm[j]);
    if (!ok)
      continue; // no solution
    int c = 0;
    for (int j = 1; j <= N; j++) {
      if (j > 1 && pos[prm[j]] < pos[prm[j - 1]])
        c++;
      if (c >= B) {
        ok = false;
        break;
      }
      ans[prm[j]] += b * c;
    }
    b *= B;
  }

  if (!ok)
    printf("-1\n");
  else {
    for (int i = 1; i <= N; i++)
      printf("%lld%c", ans[i], " \n"[i == N]);
  }
}

int main() {
  freopen("xidartros.in", "r", stdin);
  freopen("xidartros.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; t++) {
    solve_test();
  }
  return 0;
}
