#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pli pair<ll,int>
#define pil pair<int,ll>
#define pll pair<ll,ll>
#define fi first
#define se second
#define inf (INT_MAX/2-1)
#define infl (1LL<<61)
#define vi vector<int>
#define vl vector<ll>
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) begin(a),end(a)
#define y0 y5656
#define y1 y7878
#define aaa system("pause");
#define dbg(x) std::cerr<<(#x)<<": "<<(x)<<'\n',aaa
#define dbga(x,n) std::cerr<<(#x)<<"[]: ";for(int _=0;_<n;_++)std::cerr<<x[_]<<' ';std::cerr<<'\n',aaa
#define dbgs(x) std::cerr<<(#x)<<"[stl]: ";for(auto _:x)std::cerr<<_<<' ';std::cerr<<'\n',aaa
#define dbgp(x) std::cerr<<(#x)<<": "<<x.fi<<' '<<x.se<<'\n',aaa
#define dbgsp(x) std::cerr<<(#x)<<"[stl pair]:\n";for(auto _:x)std::cerr<<_.fi<<' '<<_.se<<'\n';aaa
#define maxn 10000
#define WANT_DFS 1
#define WANT_BFS 2
 
using namespace std;
 
int tip, n, k, wantNiv;
 
vi g[maxn+5];
int weight[maxn+5];
bitset<maxn+5> d[maxn+5]; ///d[i] = rucsacul nodului i.
int viz[maxn+5]; ///sunt intr-un nod. viz[x] != 0 <=> am calculat rucsacul unui fiu de-al meu cu weight[nn] = x, viz[x] = nn.
 
int niv[maxn+5], cntNiv[maxn+5]; ///doar pentru c = 1. calculeaza pe ce nivel va fi al k-lea nod din bfs.
 
void bf() {
    fill(all(niv), -1);
 
    queue<int> qu;
    qu.push(1);
 
    niv[1] = 0;
    cntNiv[0]++;
 
    while (!qu.empty()) {
        int nod = qu.front(); qu.pop();
        for (int nn: g[nod]) {
            if (niv[nn] == -1) {
                niv[nn] = 1 + niv[nod];
                cntNiv[niv[nn]]++;
                qu.push(nn);
            }
        }
    }
 
    wantNiv = 0;
    int cntNodes = 0;
 
    while (wantNiv < n-1 && cntNodes + cntNiv[wantNiv] < k) {
        cntNodes += cntNiv[wantNiv];
        wantNiv++;
    }
 
    k -= cntNodes; ///de acum ma intereseaza doar k relativ la wantNiv.
}
 
void dfWeight(int nod, int t) {
    ///in general ma intereseaza prin cati frati ma duc pana il aleg pe cel dorit.
    ///daca c = 2, greutatea unui frate este marimea subarborelui lui (i.e. dfs-ul o sa viziteze fiecare nod de acolo).
    ///daca c = 1, greutatea unui frate = cate noduri din subarborele lui sunt la nivelul wantNiv. (i.e. daca aleg alt
    ///frate nn2 inaintea celui dorit, o sa am la nivelul wantNiv weight[nn2] noduri in fata in coada.
 
    if (tip == WANT_BFS) {
        ///orice e mai jos nu mai intereseaza.
        if (niv[nod] > wantNiv) return;
        if (niv[nod] == wantNiv) {
            weight[nod] = 1;
            return;
        }
    } else {
        weight[nod] = 1;
    }
 
    for (int nn: g[nod]) {
        if (nn != t) {
            dfWeight(nn, nod);
            weight[nod] += weight[nn];
        }
    }
}
 
void df(int nod, int t) {
    if (tip == WANT_BFS && weight[nod] == 0) return;
 
    ///deja am calculat d[nod]. propag la copii.
    int i, j;
    for (int nn: g[nod]) {
        if (nn != t) {
            if (viz[weight[nn]] != 0) {
                ///nod are un alt fiu nn2 cu weight[nn] = weight[nn2] => nn, nn2 au acelasi rucsac.
                d[nn] = d[viz[weight[nn]]];
            } else {
                d[nn] = d[nod];
 
                bool passed = false;
                for (int nn2: g[nod]) {
                    if (nn2 != t) {
                        int w = weight[nn2];
                        if (weight[nn] == w && !passed) {
                            passed = true; ///nu adaug in rucsac propria mea valoare.
                        } else {
                            ///adaug intarzierea potentiala cauzata de alt fiu al lui nod in d[nn].
                            d[nn] |= (d[nn] << w);
                        }
                    }
                }
 
                if (tip == WANT_DFS) {
                    ///trebuie sa si shiftez totul cu 1 la dreapta, i.e. la un moment dat o sa cobor in dfs din tata in fiu.
                    ///daca tip == WANT_BFS, eu imi construiesc rezultate partiale si nu shiftez nimic pe parcurs.
                    d[nn] <<= 1;
                }
 
                viz[weight[nn]] = nn;
            }
        }
    }
 
    for (int nn: g[nod]) {
        if (nn != t) {
            viz[weight[nn]] = 0;
        }
    }
 
    for (int nn: g[nod]) {
        if (nn != t) {
            df(nn, nod);
        }
    }
}
 
int main() {
    ifstream cin("keidei.in");
    ofstream cout("keidei.out");
 
    cin >> tip >> n >> k;
 
    int i;
    for (i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
 
    if (tip == WANT_BFS) {
        bf();
    }
 
    dfWeight(1, 0);
 
    d[1][1] = true;
    df(1, 0);
 
    for (i = 1; i <= n; i++) {
        if (d[i][k] && (tip == WANT_DFS || (tip == WANT_BFS && niv[i] == wantNiv))) {
            cout << i << ' ';
        }
    }
 
    return 0;
}
