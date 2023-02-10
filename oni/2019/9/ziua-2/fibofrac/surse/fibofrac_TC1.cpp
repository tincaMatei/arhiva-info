// student Tudor Chiorean - Universitatea Tehnica din Cluj
// 100 puncte

#include <bits/stdc++.h>
using namespace std;

#define NMAX 1000005

ifstream fin("fibofrac.in");
ofstream fout("fibofrac.out");

int phi[NMAX], n, i, j;
long long ans;

int main()
{
    fin >> n;
    for (int i = 1; i <= n; ++i)
        phi[i] = i-1;
    for (int i = 2; i <= n; ++i)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];

    for (i = 1 ; i <= n ; i++)
        ans += ((i <= (n / 2)) ? 2 : 1 ) * phi[i];

    ans -= n - 1;

    fout << ans;

    return 0;
}
