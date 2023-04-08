#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, int> pli;
 
const int NMAX = 1e6 + 5;
 
char s[NMAX];
int nxt[NMAX], prv[NMAX];
int lst[30];
ll d[NMAX], cst[30];
 
void solve_test() {
    int N;
    int A, B, C, D;
 
    scanf("%d", &N);
    scanf("%d%d%d%d", &A, &B, &C, &D);
    scanf("%s", s);
 
    for (int i = 0; i < 26; i++) lst[i] = -1;
//    for (int i = 0; i < N; i++) prv[i] = -1;
//    for (int i = 0; i < N; i++) nxt[i] = -1;
 
    for (int i = 0; i < N; i++) {
        s[i] -= 'a';
//        int x = s[i];
//        if (lst[x] != -1) {
//            nxt[lst[x]] = i;
//            prv[i] = lst[x];
//        }
//        lst[x] = i;
    }
 
    for (int i = 1; i < N; i++) d[i] = 1LL << 60;
    d[0] = 0;
 
    for(int t = 0; t < 50; t++) {
        for(int i = 0; i < 26; i++) cst[i] = 1LL << 60;
        cst[s[0]] = d[0];
        for(int i = 1; i < N; i++) {
            d[i] = min(d[i], d[i - 1] + A);
            d[i] = min(d[i], cst[s[i]] + C);
            cst[s[i]] = d[i];
        }
        for(int i = 0; i < 26; i++) cst[i] = 1LL << 60;
        cst[s[N - 1]] = d[N - 1];
        for(int i = N - 2; i >= 0; i--) {
            d[i] = min(d[i], d[i + 1] + B);
            d[i] = min(d[i], cst[s[i]] + D);
            cst[s[i]] = d[i];
        }
    }
 
    printf("%lld\n", d[N - 1]);
}
 
int main() {
#ifndef BAPCTOOLS
    freopen("biom.in", "r", stdin);
    freopen("biom.out", "w", stdout);
#endif
    solve_test();
    return 0;
}
