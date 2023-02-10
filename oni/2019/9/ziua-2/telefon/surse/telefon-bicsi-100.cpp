#include <bits/stdc++.h>
#define int long long

using namespace std;

pair<long long, long long> Solve(int v, vector<int> dists, set<string> opts) {
    int n = dists.size();
    sort(dists.begin(), dists.end());
    long long sum = 0;
    for (auto x : dists)
        sum += x;


    int magic = sqrt(v) + 2;
    vector<int> cands = dists;

    if (!opts.count("cands_are_dists")) {
        cands.clear(); 
        for (int i = 1; i <= magic && i <= v; ++i) {
            cands.push_back(i);
            cands.push_back(v / i);
        }
        sort(cands.rbegin(), cands.rend());
        for (auto& x : cands) 
            x = v / x;
    } else {
        for (auto x : dists) 
            if (x > 1)
                cands.push_back(x / 2);
        sort(cands.begin(), cands.end());
    }

    vector<long long> bests(3, 0);
    long long now = 0;
    int l = 0, r = 0, p = -1;

    for (auto delta : cands) {
        
        
        // bests[0] = bests[1] = bests[2] = 0;
        
        int phones = v / delta;
        while (r < n && dists[r] <= delta) {
            now += dists[r];
            ++r;
        }
        while (r - l > phones) {
            now -= dists[l];
            ++l;
        } 
        bests[0] = max(bests[0], now);
        if (phones >= 1 && r < n) {
            long long xnow = now + delta;
            if (r - l == phones) xnow -= dists[l];
            bests[1] = max(bests[1], xnow);
        }
        
        while (p + 1 < n && dists[p + 1] <= 2 * delta) 
            ++p;
        
        if (phones >= 2 && p >= r) {
            long long xnow = now + dists[p];
            if (r - l >= phones - 1) xnow -= dists[l];
            if (r - l == phones) xnow -= dists[l + 1];
            bests[2] = max(bests[2], xnow);
        }

        /*
        for (auto x : dists) cerr << x << " "; cerr << endl;
        cerr << "delta: " << delta << endl;
        cerr << "(phones: " << phones << ")" << endl;
        cerr << "bests: " << bests[0] << " " << bests[1] << " " << bests[2] << endl;
        cerr << endl;
        */
    }

    long long ans = 0;
    ans = max(ans, bests[0]);
    ans = max(ans, bests[1]);
    ans = max(ans, bests[2]);

    return make_pair(sum - bests[0], sum - ans);
}

int32_t main() {
    ifstream cin("telefon.in");
    ofstream cout("telefon.out");
    int n, v; cin >> n >> v;
    int last = -1;
    vector<int> dists;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (i) dists.push_back(x - last);
        last = x;
    }
    auto p = Solve(v, dists, {});
    cout << p.first << " " << p.second << endl;

    return 0;
}
