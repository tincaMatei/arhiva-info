#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin, fok, fout;
const int NMAX = 1e6 + 10;
int base, n, k, t;
long long answer[NMAX], contestant_answer[NMAX];
pair<pair<long long, int>, int> option[NMAX];

void result(int score, const char *msg) {
  fprintf(stdout, "%d\n", score);
  fprintf(stderr, "%s\n", msg);

  if (!fin.fail())
    fin.close();
  if (!fok.fail())
    fok.close();
  if (!fout.fail())
    fout.close();

  exit(0);
}

inline int cmp(const pair<pair<long long, int>, int> A,
               const pair<pair<long long, int>, int> B) {
  if (A.first.first % base == B.first.first % base)
    return A.first.second < B.first.second;
  return A.first.first % base < B.first.first % base;
}

int main(int, char *argv[]) {
  int order;

  fin.open(argv[1]);
  fok.open(argv[2]);
  fout.open(argv[3]);

  if (fin.fail()) {
    result(0, "translate:error");
  }

  if (fout.fail()) {
    result(0, "translate:wrong-1"); // nu exista fisierul de iesire
  }

  if (fok.fail()) {
    result(0, "translate:error");
  }

  fin >> t;

  for (; t; t--) {
    fin >> n >> base >> k;

    fok >> answer[1];
    if (answer[1] != -1) {
      for (int i = 2; i <= n; i++) {
        fok >> answer[i];
      }
      for (int i = 1; i <= n; i++) {
        if (!(fout >> contestant_answer[i]))
          result(0, "translate:wrong-2");
        if (contestant_answer[i] < 0 ||
            contestant_answer[i] > 1'000'000'000'000'000'000LL) {
          result(0, "translate:wrong-3");
        }
      }
    } else {
      if (!(fout >> contestant_answer[1]))
        result(0, "translate:wrong-4");
      if (contestant_answer[1] != -1) {
        result(0, "translate:wrong-5");
      }
      for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j)
          fin >> order;
      continue;
    }

    for (int j = 1; j <= n; j++)
      option[j] = make_pair(make_pair(contestant_answer[j], j), j);
    for (int i = 1; i <= k; i++) {
      sort(option + 1, option + n + 1, cmp);
      for (int j = 1; j <= n; j++) {
        fin >> order;
        if (order != option[j].second) {
          result(0, "translate:wrong-6");
        }
      }
      for (int j = 1; j <= n; j++) {
        option[j].first.first /= base;
        option[j].first.second = j;
      }
    }
  }

  result(1, "translate:success");

  return 0;
}
