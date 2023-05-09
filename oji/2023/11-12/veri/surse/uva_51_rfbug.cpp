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
#define maxn 500

using namespace std;

ifstream fin("veri.in");
ofstream fout("veri.out");

int rf[maxn+5][maxn+5], prew[maxn+5][maxn+5];

vi genWay(int x, int y) {
    if (rf[x][y] == 1) {
        return vi{x, y};
    }

    vi wayXZ = genWay(x, prew[x][y]), wayZY = genWay(prew[x][y], y);
    wayXZ.pop_back();
    wayXZ.insert(wayXZ.end(), all(wayZY));

    return wayXZ;
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

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            rf[i][j] = inf;
        }
    }

    for (i = 1; i <= m; i++) {
        int x, y; fin >> x >> y;
        rf[x][y] = 1;
    }

    for (z = 1; z <= n; z++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (rf[i][z] < inf && rf[z][j] < inf && rf[i][j] > rf[i][z] + rf[z][j]) {
                    rf[i][j] = rf[i][z] + rf[z][j];
                    prew[i][j] = z;
                }
            }
        }
    }

    if (a == b) {
        if (tip == 1) {
            fout << rf[s][a];
        } else {
            if (s != a) afis(genWay(s, a));
            else afis(vi{a});
            afis(vi{a});
            afis(vi{a});
        }

        return 0;
    }

    int ans = inf, ansCyc = inf, bestI = -1;
    for (i = 1; i <= n; i++) {
        int distSI = rf[s][i], distIA = rf[i][a], distIB = rf[i][b]; ///problema aici.

        if (distSI < inf && distIA < inf && distIB < inf && rf[i][i] < inf) {
            if (ans > distSI + rf[i][i] + max(distIA, distIB) ||
                (ans == distSI + rf[i][i] + max(distIA, distIB) && ansCyc > distSI + rf[i][i])) {
                ans = distSI + rf[i][i] + max(distIA, distIB);
                ansCyc = distSI + rf[i][i];
                bestI = i;
            }
        }
    }

    if (tip == 1) {
        fout << ans;
        return 0;
    }

    vi waySI = (s != bestI? genWay(s, bestI): vi{s}), wayII = genWay(bestI, bestI),
       wayIA = (bestI != a? genWay(bestI, a): vi{a}), wayIB = (bestI != b? genWay(bestI, b): vi{b});

    waySI.pop_back();
    waySI.insert(waySI.end(), all(wayII));

    afis(waySI);
    afis(wayIA);
    afis(wayIB);

    return 0;
}
