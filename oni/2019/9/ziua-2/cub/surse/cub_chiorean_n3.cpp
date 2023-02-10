/**
Chiorean Tudor-Octavian
cub O(N^3)
*/

#include <bits/stdc++.h>
using namespace std;

ifstream fin("cub.in");
ofstream fout("cub.out");

int i, j, k, t, ok, nr, n, x, mul, state[4][1000000], crtState[4];
long long sol;
const int divs[] = {2, 3, 5, 7};

int main()
{
    fin >> n;
    for (i = 1 ; i <= n ; i++) {
        fin >> x;

        for (j = 0 ; j < 4 ; j++) {
            nr = 0;
            while (x % divs[j] == 0) {
                nr++;
                x /= divs[j];
                state[j][i]++;
            }

            state[j][i] %= 3;
        }
    }

    for (i = 1 ; i < n ; i++)
        for (j = i ; j <= n ; j++) {
            for (k = i ; k <= j ; k++) {
                for (t = 0 ; t < 4 ; t++) {
                    crtState[t] += state[t][k];
                }
                ok = 1;
            }

            for (t = 0 ; t < 4 ; t++) {
                if (crtState[t] % 3 != 0) {
                    ok = 0;
                    break;
                }
            }
            sol += ok;

            for (t = 0 ; t < 4 ; t++) {
                crtState[t] = 0;
            }
        }

    fout << sol;

    return 0;
}
