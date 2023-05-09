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
#define aaa (void)system("pause");
#define dbg(x) std::cerr<<(#x)<<": "<<(x)<<'\n',aaa
#define dbga(x,n) std::cerr<<(#x)<<"[]: ";for(int _=0;_<n;_++)std::cerr<<x[_]<<' ';std::cerr<<'\n',aaa
#define dbgs(x) std::cerr<<(#x)<<"[stl]: ";for(auto _:x)std::cerr<<_<<' ';std::cerr<<'\n',aaa
#define dbgp(x) std::cerr<<(#x)<<": "<<x.fi<<' '<<x.se<<'\n',aaa
#define dbgsp(x) std::cerr<<(#x)<<"[stl pair]:\n";for(auto _:x)std::cerr<<_.fi<<' '<<_.se<<'\n';aaa
#define maxn 5000

using namespace std;

int main() {
//    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//  ifstream cin("input.txt");
  ifstream cin("veri.in");
  ofstream cout("veri.out");

  int c; cin >> c;
  int n, m; cin >> n >> m;
  int s, a, b; cin >> s >> a >> b;

  if (m != n) return 0;

  int i, j, z;

  if (c == 1) {
    cout << n + max((n+a-s)%n, (n+b-s)%n);
  } else {
    cout << n << '\n';
    z = n;
    while (z--) {
      cout << s << ' ';
      s = s%n+1;
    }
    cout << s << '\n';

    cout << (n+a-s)%n << '\n';
    z = s;
    while (z != a) {
      cout << z << ' ';
      z = z%n+1;
    }
    cout << a << '\n';

    cout << (n+b-s)%n << '\n';
    z = s;
    while (z != b) {
      cout << z << ' ';
      z = z%n+1;

    }
    cout << b << '\n';
  }

  return 0;
}
