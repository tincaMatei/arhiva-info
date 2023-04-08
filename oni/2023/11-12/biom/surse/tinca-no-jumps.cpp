#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

std::string str;

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

  long long cost = 0LL;
  for (int i = 1; i < (int)str.size(); ++i) {
    if (str[i] != str[i - 1])
      cost = cost + a;
    else
      cost = cost + std::min(a, c);
  }

#ifdef BAPCTOOLS
  std::cout << cost << "\n";
#else
  std::ofstream fout("biom.out");
  fout << cost;
#endif
  return 0;
}

