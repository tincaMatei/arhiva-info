// prof. Chesca Ciprian
// teoria numerelor cu simplificarea ratiei 

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
    ifstream f("pro3.in");
    ofstream g("pro3.out");

    long long a1,r1,a2,r2,n1,n2,a3,r3,n3,a12,a13,a23,r12,r13,r23,n12,n13,n23,r123,a123,n123;
    long long an1,an2,an3,an12;

    long long i,j,t,x0,y0,d;

    f >> a1 >> r1 >> n1;
    f >> a2 >> r2 >> n2;
    f >> a3 >> r3 >> n3;
    an1 = a1 + r1*(n1 - 1);
    an2 = a2 + r2*(n2 - 1);
    an3 = a3 + r3*(n3 - 1);


    //------------------------------------------------------------------------
    // determin cate elemente sunt comune sirurilor 1 si 2
    // ecuatia r1*x - r2*y = (a2 - r2) - (a1 - r1)
    // ecuatia are solutii daca cmmdc(r1,r2) divide (a2 - r2) - (a1 - r1)

    d=cmmdc(r1,r2);
    t = (a2 - r2) - (a1 - r1);
    if (t%d==0) // ecuatia are solutii
    {
        //determin primul element comun celor doua siruri
        i=1;j=1;x0=0;y0=0;
        while (i<=n1 && j<=n2)
        {
          if (a1+r1*(i-1) < a2+r2*(j-1)) i++;
          if (a1+r1*(i-1) > a2+r2*(j-1)) j++;
          if (a1+r1*(i-1) == a2+r2*(j-1)) {x0 = i; y0 = j; break;}
        }

        if (x0 == 0) {a12 = 0; r12 = 0; n12 = 0;}
        else
        {
        a12 = a1 + r1*(x0 - 1);
        r12 = (r1*r2)/d;


        if (an1 < an2)
            n12 = (an1 - a12)/r12 + 1;
           else
            n12 = (an2 - a12)/r12 + 1;

        an12 = a12 + r12*(n12 - 1);
            //g<< x0<<" "<< y0 <<"\n";
        }
     }
    else // ecuatia nu are solutii
    {a12 = 0;r12 = 0;n12 = 0;}


    //---------------------------------------------------------------------
    // determin cate elemente sunt comune sirurilor 1 si 3
    // ecuatia r1*x - r3*y = (a3 - r3) - (a1 - r1)
    // ecuatia are solutii daca cmmdc(r1,r3) divide (a3 - r3) - (a1 - r1)

    d=cmmdc(r1,r3);
    t = (a3 - r3) - (a1 - r1);
    if (t%d==0) // ecuatia are solutii
    {
        //determin primul element comun celor doua siruri
        i=1;j=1;x0=0;y0=0;
        while (i<=n1 && j<=n3)
        {
          if (a1+r1*(i-1) < a3+r3*(j-1)) i++;
          if (a1+r1*(i-1) > a3+r3*(j-1)) j++;
          if (a1+r1*(i-1) == a3+r3*(j-1)) {x0 = i; y0 = j; break;}
        }
        if (x0 == 0) {a13 = 0; r13 = 0; n13 = 0;}
        else
        {
        a13 = a1 + r1*(x0 - 1);
        r13 = (r1*r3)/d;
        if (an1 < an3)
            n13 = (an1 - a13)/r13 + 1;
          else
            n13 = (an3 - a13)/r13 + 1;

        //g<< x0<<" "<< y0 <<"\n";
        }
    }
    else // ecuatia nu are solutii
    {a13 = 0;r13 = 0;n13 = 0;}



    //---------------------------------------------------------------------
    // determin cate elemente sunt comune sirurilor 2 si 3
    // ecuatia r2*x - r3*y = (a3 - r3) - (a2 - r2)
    // ecuatia are solutii daca cmmdc(r2,r3) divide (a3 - r3) - (a2 - r2)

    d=cmmdc(r2,r3);
    t = (a3 - r3) - (a2 - r2);
    if (t%d==0) // ecuatia are solutii
    {
        //determin primul element comun celor doua siruri
        i=1;j=1;x0=0;y0=0;
        while (i<=n2 && j<=n3)
        {
          if (a2+r2*(i-1) < a3+r3*(j-1)) i++;
          if (a2+r2*(i-1) > a3+r3*(j-1)) j++;
          if (a2+r2*(i-1) == a3+r3*(j-1)) {x0 = i; y0 = j;break;}
        }
        if (x0 == 0) {a23 = 0; r23 = 0; n23 = 0;}
        else
        {
        a23 = a2 + r2*(x0 - 1);
        r23 = (r2*r3)/d;
        if (an2 < an3)
            n23 = (an2 - a23)/r23 + 1;
           else
            n23 = (an3 - a23)/r23 + 1;

        //g<< x0<<" "<< y0 <<"\n";
        }
    }
    else // ecuatia nu are solutii
    {a23 = 0;r23 = 0;n23 = 0;}



    //---------------------------------------------------
    // determin cate elemente comune au cele 3 siruri
    if (n12 && n23 && n13)
    {
        // prima progresie este a12,r12,n12 si a doua este a3,r3,n3
        d=cmmdc(r12,r3);
        t = (a3 - r3) - (a12 - r12);

        if (t%d==0) // ecuatia are solutii
            {
            //determin primul element comun celor doua progresii
            i=1;j=1;x0=0;y0=0;
            while (i<=n12 && j<=n3)
            {
              if (a12+r12*(i-1) < a3+r3*(j-1)) i++;
              if (a12+r12*(i-1) > a3+r3*(j-1)) j++;
              if (a12+r12*(i-1) == a3+r3*(j-1)) {x0 = i; y0 = j; break;}
            }

            if (x0 == 0) {a123 = 0; r123 = 0; n123 = 0;}
                else
                {
                // g << a12 << " " << r12 << " " << x0 <<" " << a123 << "\n";
                a123 = a12 + r12*(x0 - 1);
                r123 = (r12*r3)/d;
                if (an12 < an3)
                    n123 = (an12 - a123)/r123 + 1;
                  else
                    n123 = (an3 - a123)/r123 + 1;
                //g<< x0<<" "<< y0 <<"\n";
                }
            }
            else
                {a123 = 0; r123 = 0; n123 = 0;}
    }
    else
        {a123 = 0; r123 = 0; n123 = 0;}



    // aplic PINEX
    //g<< " ------------------------------------------"<<"\n";
    

    g << n1 + n2 + n3 - n12 - n13 - n23 + n123;

    f.close();
    g.close();

    return 0;
}
