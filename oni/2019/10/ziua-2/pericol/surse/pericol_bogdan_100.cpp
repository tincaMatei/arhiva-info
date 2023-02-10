#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("pericol.in");
    ofstream cout("pericol.out");

    int n; cin >> n;
    vector<int> v(n);
    for (auto& it : v)
        cin >> it;
    
    int vmax = *max_element(v.begin(), v.end()) + 5;
    vector<int> frecv(vmax);
    for (auto&& it : v)
        frecv[it]++;

    int elementarCount = 0;
    vector<int> elementars(vmax);
    vector<bool> cannotElementar(vmax);
    vector<int> countMult(vmax);
    vector<int> isPrime(vmax, true); isPrime[1] = false;
    vector<int> sign(vmax, 1);
    vector<int> maxMult(vmax);
    for (int i = 1; i < vmax; ++i) {
        if (!cannotElementar[i])
            elementars[elementarCount++] = i;
        if (isPrime[i]) {
            if (1LL * i * i < vmax) {
                for (int j = i * i; j < vmax; j += i*i)
                    cannotElementar[j] = true;
            }
        }
        for (int j = i; j < vmax; j += i) {
            countMult[i] += frecv[j];
            if (frecv[j])
                maxMult[i] = max(maxMult[i], j);
            if (isPrime[i]) {
                sign[j] *= -1;
                if (j != i)
                    isPrime[j] = false;
            }
        }
    }

    // vector<long long> raspuns(vmax);
    // for (int gcd = 1; gcd < vmax; ++gcd) {
    //     if (!countMult[gcd])
    //         continue;
    //     if (countMult[gcd] == 1 && frecv[gcd] == 0)
    //         continue;
    //     if (countMult[gcd] == 1) {
    //         raspuns[gcd] += gcd;
    //         continue;
    //     }
    //     if (countMult[gcd] == 2) {
    //         if (frecv[gcd] == 1) {
    //             raspuns[gcd] += gcd + gcd;
    //             raspuns[maxMult[gcd]] += gcd;
    //             continue;
    //         }
    //         if (frecv[gcd] == 2) {
    //             raspuns[gcd] += gcd + gcd;
    //             continue;
    //         }
    //     }

    //     for (int i = 0; i < elementarCount; ++i) {
    //         int elem = elementars[i];
    //         if (1LL * elem * gcd >= vmax)
    //             break;
    //         int prod = elem * gcd;
    //         if (!countMult[prod])
    //             continue;
    //         for (int j = prod; j < vmax; j += prod)
    //             raspuns[j] += 1LL * sign[elem] * countMult[prod] * gcd;
    //     }
    // }

    vector<long long> coef(vmax);
    for (int i = 0; i < elementarCount; ++i) {
        int elem = elementars[i];
        for (int p = elem; p < vmax; p += elem)
            coef[p] += 1LL * sign[elem] * (p / elem);
    }

    vector<long long> raspuns(vmax);
    for (int p = 1; p < vmax; ++p) {
        for (int i = p; i < vmax; i += p) {
            raspuns[i] += coef[p] * countMult[p];
        }
    }

    for (int i = 0; i < n; ++i)
        cout << raspuns[v[i]] - v[i] << ' ';
    cout << '\n';

    return 0;
}
