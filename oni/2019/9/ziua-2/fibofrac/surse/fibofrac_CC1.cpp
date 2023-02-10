// Brute force
// O(n^2)

#include <fstream>

using namespace std;


long long fib[1000001];

long long cmmdc(long long a, long long b)
{
    long long d=a,i=b,r=d%i;
    while (r)
    {
        d=i;
        i=r;
        r=d%i;
    }
    return i;
}



int main()
{
    long long i,j,n,sol;
    ifstream f("fibofrac.in");
    ofstream g("fibofrac.out");
    f >> n;

    fib[1]=1;fib[2]=1;
    for(i=3;i<=n;i++)
        fib[i]=fib[i-1]+fib[i-2];



    sol=0;
    for(i=2;i<n;i++)
      for(j=i+1;j<=n;j++)
            if (cmmdc(fib[i],fib[j])==1) sol++;
        g<<sol<<" ";

    f.close();
    g.close();

    return 0;
}
