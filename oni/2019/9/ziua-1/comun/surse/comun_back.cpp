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
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        maxx = max(maxx, v[i]);
    }

    long long ap = 0;
    for (auto x : v) 
        ap |= (1LL << (x - 1));

    vector<int> calc(ap + 1, 0);
    for (int i = 1; i <= ap; ++i) {
        for (int j = 0; j < maxx; ++j) {
            if (i & (1LL << j))
                calc[i] = gcd(calc[i], j + 1);
        }
        --calc[i];
    }
    
    for (int found = 1; found >= 0; --found) {
        for (int msk = 1; msk <= ap; ++msk) {
            if ((msk & ap) != msk) continue;
            int gc = calc[msk];
            if ((ap & (1LL << gc)) && !(msk & (1LL << gc))) {
                ap ^= (1LL << gc);
                found = 1;
                break;
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < maxx; ++i) {
        if (ap & (1 << i))
            ans.push_back(i + 1);
    }

    cout << ans.size() << endl;
    for (auto x : ans) 
        cout << x << " ";
    cout << endl;
    
    return 0;
}