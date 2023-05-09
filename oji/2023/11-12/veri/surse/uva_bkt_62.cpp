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
#define aaa (void)system("read -r -p \"Press enter to continue...\" key");
#define dbg(x) std::cerr<<(#x)<<": "<<(x)<<'\n',aaa
#define dbga(x,n) std::cerr<<(#x)<<"[]: ";for(int _=0;_<n;_++)std::cerr<<x[_]<<' ';std::cerr<<'\n',aaa
#define dbgs(x) std::cerr<<(#x)<<"[stl]: ";for(auto _:x)std::cerr<<_<<' ';std::cerr<<'\n',aaa
#define dbgp(x) std::cerr<<(#x)<<": "<<x.fi<<' '<<x.se<<'\n',aaa
#define dbgsp(x) std::cerr<<(#x)<<"[stl pair]:\n";for(auto _:x)std::cerr<<_.fi<<' '<<_.se<<'\n';aaa
#define maxn 5000

using namespace std;

ifstream fin("veri.in");
ofstream fout("veri.out");

vi g[maxn+5], gt[maxn+5];
int da[maxn+5], db[maxn+5], prewA[maxn+5], prewB[maxn+5];
bool viz[maxn+5];

int ans = inf;

vi way, bestWay;
void df(int nod) {
    way.pb(nod);
    if (viz[nod]) {
        ///am inchis un ciclu.
        if (ans > sz(way)-1 + max(da[nod], db[nod])) {
            bestWay = way;
            ans = sz(way)-1 + max(da[nod], db[nod]);
        }

        way.pop_back();
        return;
    }

    if (ans <= sz(way)-1 + max(da[nod], db[nod])) {
        ///nu am putut sa inchei un ciclu aici si orice as incheia in continuare nu o sa imi imbunatateasca solutia.

        way.pop_back();
        return;
    }

    viz[nod] = true;

    for (int nn: g[nod]) {
        df(nn);
    }

    way.pop_back();
    viz[nod] = false;
}

void bf(int n, int src, int *d, int *p) {
    queue<int> qu;
    fill(d+1, d+n+1, inf);

    d[src] = 0;
    qu.push(src);

    while (!qu.empty()) {
        int nod = qu.front();
        qu.pop();

        for (int nn: gt[nod]) {
            if (d[nn] > 1 + d[nod]) {
                d[nn] = 1 + d[nod];
                p[nn] = nod;
                qu.push(nn);
            }
        }
    }
}

vi genWay(int *p, int src, int dst) {
    vi sol(1, dst);
    while (sol.back() != src) {
        sol.pb(p[sol.back()]);
    }

    return sol;
}

void afis(vi x) {
    assert(sz(x) > 0);
    fout << sz(x) - 1 << '\n';
    for (int y: x) fout << y << ' ';
    fout << '\n';
}

int main() {
    int tip; fin >> tip;
    int n, m; fin >> n >> m;
    int s, a, b; fin >> s >> a >> b;

    int i, j, z;

    for (i = 1; i <= m; i++) {
        int x, y; fin >> x >> y;
        g[x].pb(y);
        gt[y].pb(x);
    }

    bf(n, a, da, prewA);

    if (a == b) {
        if (tip == 1) {
            fout << da[s];
        } else {
            afis(genWay(prewA, a, s));
            afis(vi{a});
            afis(vi{a});
        }

        return 0;
    }

    bf(n, b, db, prewB);
    df(s);

    if (tip == 1) {
        fout << ans;
        return 0;
    }

    afis(bestWay);
    afis(genWay(prewA, a, bestWay.back()));
    afis(genWay(prewB, b, bestWay.back()));

    return 0;
}
