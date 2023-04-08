//Autor: Patcas Csaba
#include <vector> 
#include <string>  
#include <cstdio> 
#include <iostream>  

using namespace std;

#define ULL unsigned long long 
#define VI vector <int> 
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i) 

#define IN_FILE "pietricele.in" 
#define OUT_FILE "pietricele.out" 

int c, n, k;
string s;
VI a(26);
vector <ULL> part;

bool possible(ULL mn)
{
    int blocks = 0;
    ULL sum = 0;
    FOR(i, 0, n - 1)
    {
        sum += a[s[i] - 'a'];
        if (sum >= mn)
        {
            ++blocks;
            sum = 0;
        }
    }
    return blocks >= k;
}

int main()
{
    freopen(IN_FILE, "r", stdin);
    freopen(OUT_FILE, "w", stdout);

    cin >> c >> n >> k >> s;
    FOR(i, 0, 25) cin >> a[i];

    part.resize(n);
    part[0] = a[s[0] - 'a'];
    FOR(i, 1, n - 1) part[i] = part[i - 1] + a[s[i] - 'a'];

    if (c == 1)
    {
        ULL best = part[n - k];
        FOR(i, n - k + 1, n - 1) best = max(best, part[i] - part[i - (n - k + 1)]);
        cout << best;
    }
    else
    {
        ULL l = 0, r = part[n - 1] + 1;
        while (r - l > 1)
        {
            ULL  m = (l + r) / 2;
            if (possible(m)) l = m;
            else r = m;
        }
        cout << l;
    }

    return 0;
}
