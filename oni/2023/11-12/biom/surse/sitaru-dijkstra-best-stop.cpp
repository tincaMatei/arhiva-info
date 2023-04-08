#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, int> pli;
 
const int NMAX = 1e6 + 5;
 
char s[NMAX];
int nxt[NMAX], prv[NMAX];
int lst[30];
ll d[NMAX];
priority_queue<pli, vector<pli>, greater<pli>> q;
 
void solve_test() {
    int N;
    int A, B, C, D;
 
    scanf("%d", &N);
    scanf("%d%d%d%d", &A, &B, &C, &D);
    scanf("%s", s);
 
    for (int i = 0; i < 26; i++) lst[i] = -1;
    for (int i = 0; i < N; i++) prv[i] = -1;
    for (int i = 0; i < N; i++) nxt[i] = -1;
 
    for (int i = 0; i < N; i++) {
        int x = s[i] - 'a';
        if (lst[x] != -1) {
            nxt[lst[x]] = i;
            prv[i] = lst[x];
        }
        lst[x] = i;
    }
 
    for (int i = 1; i < N; i++) d[i] = 1LL << 60;
    d[0] = 0;
 
    q.push({0, 0});
    if(N > 100000) {
        ll maxval = 1LL * A * (N - 1);
        while (!q.empty()) {
            auto pr = q.top();
            q.pop();
            int x = pr.second;
            if(x == N - 1) break;
            if(d[x] > maxval)  continue;
 
            if (x < N - 1 && d[x + 1] > d[x] + A) {
                d[x + 1] = d[x] + A;
                q.push({d[x + 1], x + 1});
            }
 
            if (x > 0 && d[x - 1] > d[x] + B) {
                d[x - 1] = d[x] + B;
                q.push({d[x - 1], x - 1});
            }
 
            if (nxt[x] != -1 && d[nxt[x]] > d[x] + C) {
                d[nxt[x]] = d[x] + C;
                q.push({d[nxt[x]], nxt[x]});
            }
 
            if (prv[x] != -1 && d[prv[x]] > d[x] + D) {
                d[prv[x]] = d[x] + D;
                q.push({d[prv[x]], prv[x]});
            }
        }
    } else {
        while (!q.empty()) {
            auto pr = q.top();
            q.pop();
            int x = pr.second;
 
            if (x < N - 1 && d[x + 1] > d[x] + A) {
                d[x + 1] = d[x] + A;
                q.push({d[x + 1], x + 1});
            }
 
            if (x > 0 && d[x - 1] > d[x] + B) {
                d[x - 1] = d[x] + B;
                q.push({d[x - 1], x - 1});
            }
 
            if (nxt[x] != -1 && d[nxt[x]] > d[x] + C) {
                d[nxt[x]] = d[x] + C;
                q.push({d[nxt[x]], nxt[x]});
            }
 
            if (prv[x] != -1 && d[prv[x]] > d[x] + D) {
                d[prv[x]] = d[x] + D;
                q.push({d[prv[x]], prv[x]});
            }
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
