#include <bits/stdc++.h>

const int MAX_N = 1000000;

std::vector<int> graph[1+MAX_N];
int father[1+MAX_N];
int subtree[1+MAX_N], dep[1+MAX_N];

void predfs(int node, int father_dfs = 0) {
  father[node] = father_dfs;
  subtree[node] = 1;

  for (auto it: graph[node])
    if (it != father_dfs) {
      dep[it] = dep[node] + 1;
      predfs(it, node);
      subtree[node] += subtree[it];
    }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  predfs(1);

  for (int i = 0; i < q; ++i) {
    int x, y, h;

    scanf("%d%d%d", &x, &y, &h);
  
    std::vector<std::pair<int, int> > a, b;
    int swx = 0, swy = 0;
    while (x != y) {
      if (dep[x] > dep[y]) {
        a.push_back({x, subtree[x] - swx});
        swx = subtree[x];
        x = father[x];
      } else {
        swy = subtree[y];
        b.push_back({y, subtree[y] - swy});
        y = father[y];
      }
    }
    a.push_back({x, n - swx - swy});

    std::vector<std::pair<int, int> > chain;
    for (auto it: a)
      chain.push_back(it);
    std::reverse(b.begin(), b.end());
    for (auto it: b)
      chain.push_back(it);

    int pos = 0;
    long long res = 0LL;
    while (pos < (int)chain.size() && h > 0) {
      res = res + (long long)chain[pos].second * h;
      pos++;
      h--;
    }

    printf("%lld\n", res);
  }

  return 0;
}

