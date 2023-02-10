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

vector<bool> Sparsify(vector<bool> vals) {
    for (int i = 1; i < (int)vals.size(); ++i) {
        if (!vals[i]) continue;
        int all_gcd = 0;
        for (int j = i + i; j < (int)vals.size(); j += i) {
            if (vals[j])
                all_gcd = gcd(all_gcd, j);
        }
        if (all_gcd == i)
            vals[i] = false;
    }
    return vals;
}

int main() {
    ifstream cin("comun.in");
    ofstream cout("comun.out");
    int n; cin >> n;
    vector<bool> v(100001, false);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; v[x] = true;
    }
    v = Sparsify(v);
    vector<int> out;
    for (int i = 0; i < (int)v.size(); ++i)
        if (v[i]) 
        out.push_back(i);
    
    cout << out.size() << endl;
    for (auto x : out) 
        cout << x << " ";
    cout << endl;
    
    return 0;

}