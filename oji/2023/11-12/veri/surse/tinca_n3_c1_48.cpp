#include <bits/stdc++.h>

const int MAX_N = 5000;

bool adj[1+MAX_N][1+MAX_N];
int best_path[1+MAX_N][1+MAX_N];
int best_cut[1+MAX_N][1+MAX_N];

void run_roy_floyd(int n) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (i == j)
        best_path[i][j] = 0;
      else if (adj[i][j])
        best_path[i][j] = 1;
      else
        best_path[i][j] = 2 * MAX_N + 1;

  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (best_path[i][k] + best_path[k][j] < best_path[i][j]) {
          best_path[i][j] = best_path[i][k] + best_path[k][j];
          best_cut[i][j] = k;
        }
}

int cycle[1+MAX_N], prev_cycle[1+MAX_N];

void detect_cycles(int n) {
  for (int i = 1; i <= n; ++i)
    cycle[i] = 2 * MAX_N + 1;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      if (i != j) {
        int cycle_len = best_path[i][j] + 1;
        if (adj[j][i] == 1 && cycle_len < cycle[i]) {
          cycle[i] = cycle_len;
          prev_cycle[i] = j;
        }
      }
    }
}

std::vector<int> append(std::vector<int>& a, std::vector<int>& b) {
  std::vector<int> res = a;
  for (auto it: b)
    res.push_back(it);
  return res;
}

std::vector<int> reconstruct_between(int from, int to) {
  int cut = best_cut[from][to];

  if (from == to)
    return {};

  if (best_path[from][to] == 1)
    return {};

  std::vector<int> half1, half2;
  half1 = reconstruct_between(from, cut);
  half2 = reconstruct_between(cut, to);

  half1.push_back(cut);
  
  return append(half1, half2);
}

std::vector<int> reconstruct_path(int from, int to) {
  std::vector<int> res, between;

  res.push_back(from);
  
  between = reconstruct_between(from, to);
  for (auto it: between)
    res.push_back(it);
  
  if (from != to)
    res.push_back(to);

  return res;
}

std::vector<int> reconstruct_cycle(int node) {
  std::vector<int> res;

  res = reconstruct_path(node, prev_cycle[node]);
  res.push_back(node);

  return res;
}

void print_path(FILE *fout, std::vector<int>& path) {
  fprintf(fout, "%lu\n", path.size() - 1);
  for (auto it: path)
    fprintf(fout, "%d ", it);
  fprintf(fout, "\n");
}

int main() {
  int c;
  int n, m;
  int S, A, B;

  FILE *fin = fopen("veri.in", "r");
  
  fscanf(fin, "%d", &c);
  fscanf(fin, "%d%d", &n, &m);
  fscanf(fin, "%d%d%d", &S, &A, &B);

  for (int i = 0; i < m; ++i) {
    int x, y;
    fscanf(fin, "%d%d", &x, &y);
    adj[x][y] = true;
  }
  
  fclose(fin);

  run_roy_floyd(n);
  detect_cycles(n);

  int best_path_len = 2 * MAX_N + 1;
  std::vector<int> common, path_A, path_B;

  for (int i = 1; i <= n; ++i) {
    int common_len = best_path[S][i] + cycle[i];
    int best_len = std::max(common_len + best_path[i][A],
                            common_len + best_path[i][B]);

    std::vector<int> current_common, cycle, current_path_A, current_path_B;

    if (best_len <= best_path_len) {
      current_common = reconstruct_path(S, i);
      current_common.pop_back();
      cycle = reconstruct_cycle(i);
      current_common = append(current_common, cycle);
      current_path_A = reconstruct_path(i, A);
      current_path_B = reconstruct_path(i, B);

      if (best_len == best_path_len && (common.size() == 0 ||
            common_len < (int)common.size() - 1)) {
        common = current_common;
        path_A = current_path_A;
        path_B = current_path_B;
      } else if (best_len < best_path_len) {
        common = current_common;
        path_A = current_path_A;
        path_B = current_path_B;
      }

      best_path_len = best_len;
    }
  }

  FILE *fout = fopen("veri.out", "w");
  if (c == 1)
    fprintf(fout, "%d", best_path_len);
  /*else {
    print_path(fout, common);
    print_path(fout, path_A);
    print_path(fout, path_B);
  }*/
  fclose(fout);
  return 0;
}

