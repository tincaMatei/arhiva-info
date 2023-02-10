#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ifstream cin("comun.in");
    ofstream cout("comun.out");
    int n; cin >> n;
    vector<int> v(n);
    int maxx = 0;
    for (auto& x : v) {
        cin >> x;
        maxx = max(maxx, x);
    }

    vector<bool> w(maxx + 1);
    for (auto x : v)
        w[x] = true;

    for (int x = maxx; x >= 1; --x) {
        if (w[x] == false) continue;

        for (int pos = 0; pos < (int)v.size(); ++pos) {
            int y = v[pos];
            int gc = gcd(x, y);
            if (gc < x && gc < y)
                w[gc] = false;
        }
    }

    v.clear();
    for (int i = 1; i <= maxx; ++i)
        if (w[i])
            v.push_back(i);
    
    cout << v.size() << endl;
    for (auto x : v) 
        cout << x << " ";
    cout << endl;
    
    return 0;
}