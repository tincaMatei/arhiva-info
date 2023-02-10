// cub_em - Brut 50p
#include <fstream>
using namespace std;
int v[1048576];
int cod(int x)
{
    int i,n=0,c,d[]={2,3,5,7};
    for (i=0;i<4;i++)
    {
       c=0;
       while (x%d[i]==0)
         { c++; x/=d[i]; }
       n=n*10+c%3;
    }
    return n;
}
int main()
{
    ifstream fi("cub.in"); ofstream fo("cub.out");
    int n,i,j,x;
    fi>>n;
    for (i=1;i<=n;i++)
    {  fi>>x; v[i]=cod(x); }
    for (i=1;i<=n;i++)
    {
        x=v[i-1]+v[i];
        v[i]=x%10%3+10*(x/10%10%3)+100*(x/100%10%3)+1000*(x/1000%3);
    }
    x=0;
    for (i=1;i<=n;i++) for (j=i;j<=n;j++)
        if (v[j]==v[i-1]) x++;
    fo<<x<<"\n";
    return 0;
}
