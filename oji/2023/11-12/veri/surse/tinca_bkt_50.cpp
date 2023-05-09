#include <bits/stdc++.h>

const int MAX_N = 5000;

int best_path_length = 2 * MAX_N + 1;

std::vector<int> best_path_A;
std::vector<int> best_path_B;
std::vector<int> best_common;

std::vector<int> graph[1+MAX_N];

bool vis[1+MAX_N];
bool vis2[1+MAX_N];

std::vector<int> find_best_path(int node, int target, std::vector<int>& path) {
  vis2[node] = true;
  path.push_back(node);
  
  std::vector<int> best;
  
  if (node == target) {
    best = path;  
    path.pop_back();
    vis2[node] = false;
    return best;
  }


  for (auto it: graph[node]) {
    if (!vis2[it]) {
      std::vector<int> res = find_best_path(it, target, path);
      if (res.size() != 0 && (res.size() < best.size() || best.size() == 0))
        best = res;
    }
  }

  vis2[node] = false;
  path.pop_back();

  return best;
}

void bkt(int node, std::vector<int>& common, 
                   std::vector<int>& path_A, 
                   std::vector<int>& path_B,
                   int A, int B) {
  vis[node] = true;
  common.push_back(node);

  for (auto it: graph[node])
    if (!vis[it])
      bkt(it, common, path_A, path_B, A, B);
    else {
      common.push_back(it);

      path_A.clear();
      path_B.clear();
      path_A = find_best_path(it, A, path_A);
      path_B = find_best_path(it, B, path_B);
      
      int len = std::max(common.size() + path_A.size() - 2,
                         common.size() + path_B.size() - 2);

      if (path_A.size() != 0 && path_B.size() != 0 && common.size() != 0 && len < best_path_length) {
        best_path_length = len;
        best_common = common;
        best_path_A = path_A;
        best_path_B = path_B;
      }

      common.pop_back();
    }

  common.pop_back();
  vis[node] = false;
}

void print_path(FILE *fout, std::vector<int> path) {
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
    graph[x].push_back(y);
  }

  fclose(fin);

  std::vector<int> common, path_A, path_B;

  bkt(S, common, path_A, path_B, A, B);

  FILE *fout = fopen("veri.out", "w");
  
  if (c == 1)
    fprintf(fout, "%d", best_path_length);
  else {
    print_path(fout, best_common);
    print_path(fout, best_path_A);
    print_path(fout, best_path_B);
  }
  fclose(fout);

  return 0;
}

