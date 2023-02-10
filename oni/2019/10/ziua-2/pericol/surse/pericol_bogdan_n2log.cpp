#include <bits/stdc++.h>
using namespace std;

const int DIM = 200005;
const int VMAX = 5000005;

int v[DIM];

inline int gcd(int x, int y) {
    while (y) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

int main() {
    ifstream cin("pericol.in");
    ofstream cout("pericol.out");    

    int n; cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    for (int i = 0; i < n; ++i) {
        long long res = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            res += gcd(v[i], v[j]);
        }
        cout << res << ' ';
    }
    cout << '\n';

    return 0;
}
