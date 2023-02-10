// prof. Chesca Ciprian
// O(nsqrt(n))

#include <fstream>
#define nmax 1000003

using namespace std;

long long T=0;
int fi[nmax],t;

char v[nmax];
int prime[nmax/5],nr=0;
int b[nmax/5],nf=0;


// Ciurul lui Eratostene
void ciur(int n)
{
  int i, j;
  for (i = 2; i <= n; ++i) {
    if (v[i] == 0) {
      prime[++nr]=i;
      for (j = i + i; j <= n; j += i) {
        v[j] = 1;
      }}}

}

//descompun in factori primi
void desc(int n)
{
    int i=1,j=0,f;
    while (n>1)
    {
        f=0;
        while (n%prime[i]==0)
                {
                 f++;
                 n=n/prime[i];
                }
        if (f) {b[++j]=prime[i];}
            else i++;
    }
    nf=j;
}


int main()
{
ifstream f("fibofrac.in");
ofstream g("fibofrac.out");

int n,i,j;
f>>n;
ciur(n);

// calculez fi(i) in O(sqrt(n))
for(i=1;i<=n;i++)
        {
        fi[i]=i;
        desc(i);
        for(j=1;j<=nf;j++)
              {
               fi[i]=fi[i]/b[j];
               fi[i]=fi[i]*(b[j]-1);
              }

        }

    for(i=1;i<=n/2;i++)
         T+=2*fi[i];

    for(i=n/2+1;i<=n;i++)
         T+=fi[i];

    g<<T - (n-2) - 3<<"\n";


f.close();
g.close();

return 0;
}



