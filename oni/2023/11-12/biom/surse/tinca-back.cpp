#include <string>
#include <deque>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

std::string str;

const int MAX_N = 1000000;
const int SIGMA = 26;
const long long INF = 1LL << 60;

int last_letter[26];
int prev_letter[MAX_N], next_letter[MAX_N];

void reset_last() {
  for (int i = 0; i < SIGMA; ++i)
    last_letter[i] = -1;
}

void create_links(int n, int* link, int start, int end, int dir) {
  reset_last();
  while (start != end) {
    int i = start;
    if (last_letter[str[i] - 'a'] != -1)
      link[i] = last_letter[str[i] - 'a'];
    else
      link[i] = -1;

    last_letter[str[i] - 'a'] = i;
    start = start + dir;
  }
}

bool vis[MAX_N];

long long bkt(int node, int n, int a, int b, int c, int d) {
  long long res = INF;

  if (node == n - 1)
    return 0LL;
  else {
    int edge[4] = {node + 1, node - 1, next_letter[node], prev_letter[node]};
    int cost[4] = {a, b, c, d};

    for (int d = 0; d < 4; ++d) {
      int to = edge[d];

      if (0 <= to && to < n && !vis[to]) {
        vis[to] = true;
        res = std::min(res, cost[d] + bkt(to, n, a, b, c, d));
        vis[to] = false;
      }
    }
  }

  return res;
}

int main() {
  int n;
  int a, b, c, d;

#ifdef BAPCTOOLS
  std::cin >> n;
  std::cin >> a >> b >> c >> d;
  std::cin >> str;
#else
  std::ifstream fin("biom.in");

  fin >> n;
  fin >> a >> b >> c >> d;
  fin >> str;
#endif

  create_links(n, prev_letter, 0, n, 1);
  create_links(n, next_letter, n - 1, -1, -1);

  vis[0] = true;
  long long best_cost = bkt(0, n, a, b, c, d);

#ifdef BAPCTOOLS
  std::cout << best_cost << "\n";
#else
  std::ofstream fout("biom.out");
  fout << best_cost << "\n";
#endif

  //print_path(n - 1);

  return 0;
}
