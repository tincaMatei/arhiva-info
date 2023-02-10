#include <fstream>
using namespace std;
ifstream f("cub.in");
ofstream g("cub.out");
int e2,e3,e5,e7,v[1000002];
int cod,viz[82],x;
int n,i,j,k,r,i1,j1,k1,r1,d[22],t[15],c[11],s[10];
unsigned long long p,sol;
int ex2[1000002],ex3[1000002],ex5[1000002],ex7[1000002];

int main()
{
    d[0]=1;i=0;
    while(d[i]<=1000000)
    {
        i++;
        d[i]=d[i-1]*2;
    }
    i--;
    t[0]=1;j=0;
    while(t[j]<=1000000)
    {
        j++;
        t[j]=t[j-1]*3;
    }
    j--;
    c[0]=1;k=0;
    while(c[k]<=1000000)
    {
        k++;
        c[k]=c[k-1]*5;
    }
    k--;
    s[0]=1;r=0;
    while(s[r]<=1000000)
    {
        r++;
        s[r]=s[r-1]*7;
    }
    r--;
    //g<<"i2="<<i<<" i3="<<j<<" i5="<<k<<" i7="<<r<<"\n"; //19 12 8 7
    // calculez numerele mai mici decat 1000000 ce sunt divizibile doar cu 2, 3 ,5 sau 7
    for(i1=0;i1<=i;i1++)
      for(j1=0;j1<=j;j1++)
        for(k1=0;k1<=k;k1++)
          for(r1=0;r1<=r;r1++)
           {
               p=1ll*d[i1]*t[j1]*c[k1]*s[r1];
               if(p<=1000000)
                {
                    ex2[p]=i1;
                    ex3[p]=j1;
                    ex5[p]=k1;
                    ex7[p]=r1;
                    //w++;
                }
           }
     //g<<"nr numere ="<<w<<"\n";// 1273
     // citesc numerele si formez exponentii cumulati ai lui 2, 3 ,5 si 7
     e2=0;e3=0;e5=0;e7=0;
     f>>n;
     for(i=1;i<=n;i++)
        f>>v[i];
     for(i=1;i<=n;i++)
     {
         x=v[i]; ;
         e2=(e2+ex2[x])%3;
         e3=(e3+ex3[x])%3;
         e5=(e5+ex5[x])%3;
         e7=(e7+ex7[x])%3;
         cod=e2*27+e3*9+e5*3+e7;//scriu in baza 3
         viz[cod]++;
     }
     sol=viz[0];
     for(i=0;i<=80;i++)
       sol=sol+viz[i]*(viz[i]-1)/2;
     g<<sol<<'\n' ;
     g.close();
     return 0;
}
