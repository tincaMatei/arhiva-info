#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Tree {
  Tree(int size)
      : edges(size), depth(size, 0), count(size, 1), parent(size, 0),
        link(size, 0), total(size, 0) {}

  void add_edge(int x, int y) {
    edges[x].emplace_back(y);
    edges[y].emplace_back(x);
  }

  void prepare(int node = 0) {
    int p = parent[node];
    int g = link[p];
    int gp = link[g];
    if (depth[p] - depth[g] == depth[g] - depth[gp])
      link[node] = gp;
    else
      link[node] = p;

    for (auto x : edges[node]) {
      if (x == parent[node])
        continue;
      parent[x] = node;
      depth[x] = depth[node] + 1;
      prepare(x);
      count[node] += count[x];
    }
  }

  int lca(int x, int y) {
    if (depth[x] < depth[y])
      swap(x, y);
    x = anc(x, depth[x] - depth[y]);

    if (x == y)
      return x;
    while (x != y)
      if (link[x] != link[y]) {
        x = link[x];
        y = link[y];
      } else {
        x = parent[x];
        y = parent[y];
      }
    return x;
  }

  int anc(int x, int h) {
    if (h == 0)
      return x;
    int jump = depth[x] - depth[link[x]];
    if (jump <= h)
      return anc(link[x], h - jump);
    return anc(parent[x], h - 1);
  }

  int dist(int x, int up) { return depth[x] - depth[up]; }

  void add(int node = 0) {
    total[node] += count[node];
    for (auto x : edges[node]) {
      if (x == parent[node])
        continue;
      total[x] += total[node];
      add(x);
    }
  }

  int64_t sum(int x, int up) { return total[x] - total[up]; }
  vector<vector<int>> edges;
  vector<int> depth, count, parent, link;

  vector<int64_t> total;
};

int main() {
  ios::sync_with_stdio(false);

  int N, Q;
  assert(cin >> N >> Q);
  assert(1 <= N && N <= 200 * 1000);
  assert(1 <= Q && Q <= 200 * 1000);

  Tree T(N);
  for (int i = 1; i < N; ++i) {
    int a, b;
    assert(cin >> a >> b);
    assert(1 <= a && a <= N);
    assert(1 <= b && b <= N);
    assert(a != b);
    T.add_edge(a - 1, b - 1);
  }

  T.prepare();
  T.add();

  for (int i = 0; i < Q; ++i) {
    int x, y, h;
    cin >> x >> y >> h;
    --x;
    --y;
    int c = T.lca(x, y);
    int d1 = T.dist(x, c);
    int d2 = T.dist(y, c);
    if (d1 > h) {
      y = c = T.anc(x, h);
      d1 = h;
      d2 = 0;
    } else if (d1 + d2 > h) {
      y = T.anc(y, d1 + d2 - h);
      d2 = h - d1;
    }

    // everyone has H originally
    // then we decrease 1 in all N - count[x]
    // then again in all N - parent[x]
    // then in all N - parent[parent[x]]
    // ...
    int64_t answer = int64_t(N) * (h - d1) + T.sum(x, c);
    // then we decrease in some son of c (all)
    // then some extra son
    answer -= T.sum(y, c);
    cout << answer << "\n";
  }
}
