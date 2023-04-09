// Solutie stud. Vlad-Mihai Bogdan
// Universitatea din Bucuresti
#include <bits/stdc++.h>
using namespace std;
 
const int L = 5;
const int MAXMASK = 243;
const int MAXN = (int)3e5;
const string P = "bingo";
 
ifstream in("bingo.in");
ofstream out("bingo.out");
 
int T, N;
string S;
int order[L];
int possible[MAXMASK][L], nextLeft[MAXN][L], nextRight[MAXN][L];
int seen[L][L][L][L][L];
 
int main() {
    in >> T;
    for (int i = 0; i < (int)P.size(); i++) {
        order[i] = i;
    }
    memset(seen, -1, sizeof seen);
    for (int tt = 0; tt < T; tt++) {
        in >> S;
        N = (int)S.size();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < (int)P.size(); j++) {
                nextLeft[i][j] = nextRight[i][j] = -1;
            }
        }
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < (int)P.size(); j++) {
                if (S[i - 1] == P[j]) {
                    nextLeft[i][j] = i - 1;
                } else {
                    nextLeft[i][j] = nextLeft[i - 1][j];
                }
            }
        }
        for (int i = N - 2; i >= 0; i--) {
            for (int j = 0; j < (int)P.size(); j++) {
                if (S[i + 1] == P[j]) {
                    nextRight[i][j] = i + 1;
                } else {
                    nextRight[i][j] = nextRight[i + 1][j];
                }
            }
        }
        int answer = INT_MAX;
        for (int i = 0; i < N - (int)P.size() + 1; i++) {
            int len = 0;
            if (S[i] == P[0]) {
                possible[len++][0] = i;
            }
            if (nextLeft[i][0] != -1) {
                possible[len++][0] = nextLeft[i][0];
            }
            if (nextRight[i][0] != -1) {
                possible[len++][0] = nextRight[i][0];
            }
            for (int j = 1; j < (int)P.size(); j++) {
                int count = (S[i + j] == P[j]) + (nextLeft[i + j][j] != -1) + (nextRight[i + j][j] != -1);
                int oldSize = len;
                for (int c = 1; c < count; c++) {
                    for (int k = 0; k < oldSize; k++) {
                        for (int t = 0; t < j; t++) {
                            possible[oldSize * c + k][t] = possible[k][t];
                        }
                    }
                }
                int pos = 0;
                if (S[i + j] == P[j]) {
                    for (int k = 0; k < oldSize; k++) {
                        possible[k][j] = i + j;
                    }
                    pos += oldSize;
                }
                if (nextLeft[i + j][j] != -1) {
                    for (int k = 0; k < oldSize; k++) {
                        possible[k + pos][j] = nextLeft[i + j][j];
                    }
                    pos += oldSize;
                }
                if (nextRight[i + j][j] != -1) {
                    for (int k = 0; k < oldSize; k++) {
                        possible[k + pos][j] = nextRight[i + j][j];
                    }
                    pos += oldSize;
                }
                len = pos;
            }
            for (int p = 0; p < len; p++) {
                sort(order, order + (int)P.size(), [&](int k, int j) {
                    return possible[p][k] < possible[p][j];
                });
                int swapsNeeded = 0;
                for (int j = 0; j < (int)P.size(); j++) {
                    swapsNeeded += abs(possible[p][order[j]] - (i + j));
                }
                if (seen[order[0]][order[1]][order[2]][order[3]][order[4]] != -1) {
                    swapsNeeded += seen[order[0]][order[1]][order[2]][order[3]][order[4]];
                } else {
                    int cnt = 0;
                    for (int j = 0; j < (int)P.size() - 1; j++) {
                        for (int k = j + 1; k < (int)P.size(); k++) {
                            if (possible[p][j] > possible[p][k]) {
                                cnt++;
                            }
                        }
                    }
                    seen[order[0]][order[1]][order[2]][order[3]][order[4]] = cnt;
                    swapsNeeded += cnt;
                }
                answer = min(answer, swapsNeeded);
            }
        }
        out << answer << "\n";
        S.clear();
    }
    return 0;
}