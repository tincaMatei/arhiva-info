#include <bits/stdc++.h>
using namespace std;

#define NMAX 250005

ifstream fin("comun.in");
ofstream fout("comun.out");

int n, i, j, x, valmax, gcd;
int v[NMAX];

int main()
{
    fin >> n;
    for (i = 1 ; i <= n ; i++) {
        fin >> x;
        v[x] = 1;
        valmax = max(valmax, x);
    }

    for (i = valmax - 1 ; i > 0 ; i--) {
        if (!v[i] || i + i > valmax) continue;

        gcd = 0;

        for (j = i + i ; j <= valmax ; j += i)
            if (v[j] == 1) {
                if (gcd == 0)
                    gcd = j;
                else
                    gcd = __gcd(gcd, j);
            }


        if (gcd == i)
            v[i] = 0, n--;
    }

    fout << n << '\n';
    for (i = 1 ; i <= valmax ; i++) {
        if (v[i] == 1) fout << i << ' ';
    }

    return 0;
}
