// student Alex Turdean - Universitatea Tehnica Cluj

#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

ifstream fin("pro3.in");
ofstream fout("pro3.out");

long long rez, a[4], n[4],r[4];

long long gcd(int x, int y)
{
    int r = x%y;
    while(r)
    {
        x = y;
        y = r;
        r = x%y;
    }
    return y;
}

long long inter2(int x, int y)
{
    long long maxi = min(a[x] + (n[x] - 1) * r[x], a[y] + (n[y] - 1) * r[y]);
    for(int i = 0; i < 1000000; i++)
    {
        long long termen = a[x] + i * r[x];
        if(termen > maxi)
            return 0;
        if( (termen - a[y]) % r[y] == 0 && termen >= a[y])
        {
            return (maxi - termen) / (r[x] * r[y] / gcd(r[y], r[x])) + 1;
        }
    }
    return 0;
}

long long inter3()
{
    long long maxi = min(a[1] + (n[1] - 1) * r[1], a[2] + (n[2] - 1) * r[2]);
    long long termen;
    long long ratie = r[1] * r[2] / gcd(r[1], r[2]);
    int i;
    for(i = 0; i < 1000000; i++)
    {
        termen = a[1] + i * r[1];
        if(termen > maxi)
            return 0;
        if( (termen - a[2]) % r[2] == 0 )
        {
            break;
        }
    }
    maxi = min(maxi, a[3] + (n[3] - 1) * r[3]);
    if(termen > maxi || i == 1000000)
        return 0;
    for(i = 0; i < 1000000; i++)
    {
		if(i)
        termen += ratie;
        if(termen > maxi)
            return 0;
        if( (termen - a[3]) % r[3] == 0 )
        {
            return (maxi - termen) / (ratie * r[3] / gcd(r[3], ratie)) + 1;
        }
    }
    return 0;
}

int main()
{
    for(int i = 1; i <= 3; i++)
        fin >> a[i] >> r[i] >> n[i];
    fout << n[1] + n[2] + n[3] - inter2(1, 2) - inter2(1, 3) - inter2(2, 3) + inter3() << '\n';
    return 0;
}
