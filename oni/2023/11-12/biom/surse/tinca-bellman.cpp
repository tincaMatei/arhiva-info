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

long long cost[MAX_N];

int father[MAX_N];

void print_path(int node) {
  std::vector<int> path;

  while (node != 0) {
    path.push_back(node);
    node = father[node];
  }
  path.push_back(0);

  std::reverse(path.begin(), path.end());

  printf("Path: ");
  for (auto it: path)
    printf("%d ", it);
  printf("\n");
}

bool in_queue[MAX_N];

void dijkstra(int n, int a, int b, int c, int d) {
  int cost_edge[4] = {a, b, c, d};

  for (int i = 0; i < n; ++i)
    cost[i] = INF;
  cost[0] = 0;

  std::queue<int> pq;

  pq.push(0);
  in_queue[0] = true;

  int step = 0;

  while (!pq.empty()) {
    int node = pq.front();
    pq.pop();
    in_queue[node] = false;

    step++;

    int neigh[4] = {node + 1, node - 1, next_letter[node], prev_letter[node]};

    for (int d = 0; d < 4; ++d) {
      int to = neigh[d];

      if (0 <= to && to < n && cost[node] + cost_edge[d] < cost[to]) {
        cost[to] = cost[node] + cost_edge[d];
        father[to] = node;
        if (!in_queue[to]) {
          pq.push(to);
          in_queue[to] = true;
        }
      }
    }
  }
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

  dijkstra(n, a, b, c, d);

#ifdef BAPCTOOLS
  std::cout << cost[n - 1] << "\n";
#else
  std::ofstream fout("biom.out");
  fout << cost[n - 1] << "\n";
#endif

  //print_path(n - 1);

  return 0;
}

