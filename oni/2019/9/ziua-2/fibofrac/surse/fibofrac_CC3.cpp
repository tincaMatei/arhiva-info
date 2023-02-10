// Brute force
// O(n^2) fara generarea termenilor sirului Fibonacci


#include <fstream>

using namespace std;


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


    sol=0;
    for(i=2;i<n;i++)
      for(j=i+1;j<=n;j++)
            if (cmmdc(i,j)==1 || cmmdc(i,j)==2) sol++;
    g<<sol<<" ";

    f.close();
    g.close();

    return 0;
}
