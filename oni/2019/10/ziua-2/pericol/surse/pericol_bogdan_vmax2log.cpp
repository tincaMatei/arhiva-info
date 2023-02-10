#include <bits/stdc++.h>
using namespace std;

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
    vector<int> v(n);
    for (auto& it : v)
        cin >> it;

    int vmax = *max_element(v.begin(), v.end()) + 1;
    vector<int> frecv(vmax);
    for (int i = 0; i < n; ++i)
        frecv[v[i]]++;
    
    vector<long long> raspuns(vmax);
    for (int i = 1; i < vmax; ++i) {
        if (!frecv[i])
            continue;
        for (int j = 1; j < vmax; ++j) {
            if (!frecv[j])
                continue;
            int g = gcd(i, j);
            raspuns[i] += 1LL * g * frecv[j];            
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << raspuns[v[i]] - v[i] << ' ';
    }
    cout << '\n';

    return 0;
}
