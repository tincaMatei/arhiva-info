#include <bits/stdc++.h>

const int MAX_N = 5000;
const int INF = 2 * MAX_N + 1;

std::vector<int> graph[1+MAX_N];

int dist[1+MAX_N][1+MAX_N];
int prev[1+MAX_N][1+MAX_N];

void bfs(int n, int start, int* dist, int* prev) {
  std::queue<int> coada;

  for (int i = 1; i <= n; ++i)
    dist[i] = INF;

  dist[start] = 0;
  prev[start] = start;
  coada.push(start);

  while (!coada.empty()) {
    int node = coada.front();
    coada.pop();

    for (auto it: graph[node]) {
      if (dist[it] == INF) {
        dist[it] = dist[node] + 1;
        prev[it] = node;
        coada.push(it);
      }
    }
  }
}

void append_path(int start, int end, std::vector<int>& path, 
                 bool exclude_start, 
                 bool exclude_end) {
  std::deque<int> reconstructed_path;

  // end can be reached from start
  assert(dist[start][end] != INF);

  while (end != start) {
    reconstructed_path.push_front(end);
    end = prev[start][end];
  }
  reconstructed_path.push_front(start);

  if (exclude_start)
    reconstructed_path.pop_front();
  if (exclude_end && !reconstructed_path.empty())
    reconstructed_path.pop_front();

  for (auto it: reconstructed_path)
    path.push_back(it);
}

struct Loop {
  int meeting_node, first_cycle;

  int calculate_intersection(int S, int A, int B) {
    if (meeting_node == 0 && A == B)
      return dist[S][A];
    else if (meeting_node == 0)
      return INF;

    int intersect = dist[S][meeting_node] + 1 + dist[first_cycle][meeting_node];

    return intersect;
  }

  int calculate_best_path(int S, int A, int B) {
    if (meeting_node == 0 && A == B) {
      return dist[S][A];
    } else if (meeting_node == 0) {
      return INF;
    }

    int intersect = dist[S][meeting_node] + 1 + dist[first_cycle][meeting_node];

    return std::max(intersect + dist[meeting_node][A], 
                    intersect + dist[meeting_node][B]);
  }

  void reconstruct_best_path(int S, int A, int B,
                             std::vector<int>& common,
                             std::vector<int>& path_A,
                             std::vector<int>& path_B) {
    if (meeting_node == 0) {
      append_path(S, A, common, false, false);
      append_path(A, A, path_A, false, false);
      append_path(B, B, path_B, false, false);
      return;
    }

    append_path(S, meeting_node, common, false, false);
    append_path(first_cycle, meeting_node, common, false, false);
    append_path(meeting_node, A, path_A, false, false);
    append_path(meeting_node, B, path_B, false, false);
  }
};

void print_vector(FILE *fout, std::vector<int>& path) {
  fprintf(fout, "%lu\n", path.size() - 1);
  for (auto it: path)
    fprintf(fout, "%d ", it);
  fprintf(fout, "\n");
}

int freq[1+MAX_N][1+MAX_N];

int main() {
  int c;
  int n, m;
  int S, A, B;

  FILE *fin = fopen("veri.in", "r");

  fscanf(fin, "%d", &c);
  fscanf(fin, "%d%d", &n, &m);
  fscanf(fin, "%d%d%d", &S, &A, &B);
  
  assert(1 <= n && n <= 5000);
  assert(A != B);
  assert(1 <= m && m <= n * (n - 1));

  for (int i = 0; i < m; ++i) {
    int x, y;
    fscanf(fin, "%d%d", &x, &y);
    graph[x].push_back(y);
  
    assert(x != y);
    assert(freq[x][y] == 0);
    freq[x][y]++;
  }

  fclose(fin);

  Loop best = {0, 0};

  for (int i = 1; i <= n; ++i) {
    bfs(n, i, dist[i], prev[i]);
  }

  for (int meeting = 1; meeting <= n; ++meeting) {
    for (auto first_cycle: graph[meeting]) {
      Loop potential_path = {meeting, first_cycle};

      std::pair<int, int> current_path_lengths = {
        best.calculate_best_path(S, A, B),
        best.calculate_intersection(S, A, B)
      };

      std::pair<int, int> potential_path_lengths = {
        potential_path.calculate_best_path(S, A, B), 
        potential_path.calculate_intersection(S, A, B)
      };

      if (potential_path_lengths < current_path_lengths)
        best = potential_path;
    }
  }

  FILE *fout = fopen("veri.out", "w");

  if (c == 1)
    fprintf(fout, "%d", best.calculate_best_path(S, A, B));
  else {
    std::vector<int> common, path_A, path_B;

    best.reconstruct_best_path(S, A, B, common, path_A, path_B);

    print_vector(fout, common);
    print_vector(fout, path_A);
    print_vector(fout, path_B);
  }
  fclose(fout);

  return 0;
}

