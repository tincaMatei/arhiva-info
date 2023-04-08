#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

const int MAX_N = 1000000;
const long long INF = 1LL << 60;

std::string str;
long long dp[MAX_N];
int last_letter[26];

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

  for (int i = 0; i < 26; ++i)
    last_letter[i] = -1;
  last_letter[str[0] - 'a'] = 0;

  for (int i = 1; i < n; ++i) {
    dp[i] = INF;

    if (last_letter[str[i] - 'a'] != -1)
      dp[i] = std::min(dp[i], dp[last_letter[str[i] - 'a']] + c);
    dp[i] = std::min(dp[i], dp[i - 1] + a);
  
    last_letter[str[i] - 'a'] = i;
  }

#ifdef BAPCTOOLS
  std::cout << dp[n - 1] << "\n";
#else
  std::ofstream fout("biom.out");
  fout << dp[n - 1];
#endif
  return 0;
}


