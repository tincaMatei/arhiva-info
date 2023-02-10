// prof. Chesca Ciprian
// Teoria numerelor


#include <fstream>
#define int long long

using namespace std;


struct pro
{
    long long a,r,n,an;
};


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


pro progresie(pro x, pro y)
{
// determin cate elemente sunt comune progresiilor x si y
// ecuatia r1*x - r2*y = (a2 - r2) - (a1 - r1)
// ecuatia are solutii daca cmmdc(r1,r2) divide (a2 - r2) - (a1 - r1)
// ratia progresie comune este r1*r2/cmmdc(r1,r2)


pro z;

long long d,t,i,j,x0;

d=cmmdc(x.r,y.r);
t = (y.a - y.r) - (x.a - x.r);
if (t%d==0) // ecuatia are solutii
    {
    //determin primul element comun celor doua siruri
    i=1;j=1;x0=0;
    while (i<=x.n && j<=y.n)
        {
          if (x.a+x.r*(i-1) < y.a+y.r*(j-1)) i++;
          if (x.a+x.r*(i-1) > y.a+y.r*(j-1)) j++;
          if (x.a+x.r*(i-1) == y.a+y.r*(j-1)) {x0 = i; break;}
        }

        if (x0 == 0) {z.a = 0; z.r = 0; z.n = 0;}
        else
        {
        z.a = x.a + x.r*(x0 - 1);
        z.r = (x.r*y.r)/d;

        x.an=x.a+x.r*(x.n-1);
        y.an=y.a+y.r*(y.n-1);

        if (x.an < y.an)
            z.n = (x.an - z.a)/z.r + 1;
           else
            z.n = (y.an - z.a)/z.r + 1;

        z.an = z.a + z.r*(z.n - 1);
        }
     }
    else // ecuatia nu are solutii
    {z.a = 0;z.r = 0;z.n = 0;}

return z;
}



int32_t main()
{
    ifstream f("pro3.in");
    ofstream g("pro3.out");


    pro x,y,z,xy,xz,yz,xyz;


    f >> x.a >> x.r >> x.n;
    f >> y.a >> y.r >> y.n;
    f >> z.a >> z.r >> z.n;

    xy = progresie(x,y);
    xz = progresie(x,z);
    yz = progresie(y,z);
    xyz = progresie(xy,z);

    // aplic PINEX
    g << x.n + y.n + z.n - xy.n - xz.n - yz.n + xyz.n;

    f.close();
    g.close();

    return 0;
}
