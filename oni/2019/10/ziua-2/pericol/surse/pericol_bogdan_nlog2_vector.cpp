#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("pericol.in");
    ofstream cout("pericol.out");
    
    int n; cin >> n;
    
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    
    vector<int> frecv(*max_element(v.begin(), v.end()) + 5);
    for (auto&& it : v)
        frecv[it]++;

    int vmax = (int)frecv.size();    
    vector<int> countDiv(vmax);
    for (int i = 1; i < vmax; ++i)
        for (int j = i; j < vmax; j += i)
            countDiv[j]++;
    
    vector<vector<int>> divs(vmax);
    for (int i = 1; i < vmax; ++i) {
        divs[i].resize(countDiv[i]);
        countDiv[i] = 0;
    }

    for (int i = 1; i < vmax; ++i)
        for (int j = i; j < vmax; j += i)
            divs[j][countDiv[j]++] = i;
    
    vector<int> count(vmax);
    for (int i = 1; i < vmax; ++i)
        for (int j = i; j < vmax; j += i)
            count[i] += frecv[j];

    vector<int> raspuns(vmax);
    vector<long long> ansForVal(vmax);
    for (int i = 1; i < vmax; ++i) {
        if (!frecv[i])
            continue;
        for (int j = 0; j < countDiv[i]; ++j)
            raspuns[divs[i][j]] = count[divs[i][j]];
        for (int divBigIndex = countDiv[i] - 1; divBigIndex >= 0; divBigIndex--) {
            int divBig = divs[i][divBigIndex];
            for (int divSmallIndex = countDiv[divBig] - 2; divSmallIndex >= 0; divSmallIndex--) {
                int divSmall = divs[divBig][divSmallIndex];
                raspuns[divSmall] -= raspuns[divBig];
            }
        }
        for (int j = 0; j < countDiv[i]; ++j)
            ansForVal[i] += 1LL * raspuns[divs[i][j]] * divs[i][j];
    }

    for (int i = 0; i < n; ++i)
        cout << ansForVal[v[i]] - v[i] << ' ';
    cout << '\n';

    return 0;
}
