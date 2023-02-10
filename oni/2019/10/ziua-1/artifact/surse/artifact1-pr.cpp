///ecuatie de forma v[1]*c[1]+v[2]*c[2]+...+v[10]*c[10]
///generare de aranjamente de 10 luate cate n/2 prin parcurgerea numerelor cu cel mult n cifre
///"meet-in-the-middle", sume, sortare, reprezentare in baza 2,...
#include<fstream>
#include<string.h>
#include<algorithm>
using namespace std;
ifstream fin ("artifact.in");
ofstream fout("artifact.out");
long long N,M,i,i1,j,p[92],f[92],a[12],c[92],d[92],cif[20],
    j1,j2,n,k,l,x,q,nrsol,ok,ok1,s,r,y,n1,n2,p1,nc1,nc2;
struct triplet{
    long long s,v,c;
}c1[31002],c2[31002];
bool cmp(triplet a, triplet b){
    if(a.s<b.s)return 1;
    if(a.s==b.s && a.v<b.v)return 1;
    return 0;
}
///a[] contine codurile ASCII ale literelor implicate
///p[j]=1 daca litera j este pe prima pozitie
///p[j]=0 in caz contrar
///n=numarul literelor implicate
///v[i] este valoarea temporar asociata cu litera a[i]
///c[j] este coeficientul din ecuatie asociat literei j
char t[12];
int ff(long long n1, long long r1, long long r2, long long &nc1, triplet c1[]){
    long long i,j,x,ok,s,y,p1;
    p1=1;
    nc1=0;
    for(i=1;i<=n1;i++)p1=p1*10;
    for(i=0;i<p1;i++){
        for(j=0;j<=9;j++){
            cif[j]=0;
        }
        x=i;ok=1;s=0;y=0;
        for(j=r1;j<=r2;j++){
            cif[x%10]++;
            if(cif[x%10]>1){
                ok=0;break;
            }
            if(x%10==0 && p[a[j]]==1){
                ok=0;break;
            }
            y=y+(1<<(x%10));
            s=s+(x%10)*c[a[j]];
            x=x/10;
        }
        if(ok==1){
            nc1++; c1[nc1].s=s; c1[nc1].v=y; c1[nc1].c=1;
        }
    }
    sort(c1+1,c1+1+nc1,cmp);
    j=1;
    for(i=2;i<=nc1;i++){
        if(c1[j].s==c1[i].s && c1[j].v==c1[i].v){
            c1[j].c++;
        }
        else{j++; c1[j]=c1[i];}
    }
    nc1=j;
    return 0;
}
int main(){
    fin>>N>>M;
    for(i=1;i<=N;i++){
        fin>>t; l=strlen(t);
        if(l>1)p[t[0]]=1;
        q=1;
        for(j=l-1;j>=0;j--){
            f[t[j]]++;
            c[t[j]]+=q;
            q*=10;
        }
    }
    for(i=1;i<=M;i++){
        fin>>t; l=strlen(t);
        if(l>1)p[t[0]]=1;
        q=1;
        for(j=l-1;j>=0;j--){
            f[t[j]]++;
            c[t[j]]-=q;
            q*=10;
        }
    }

    n=0;
    for(i=65;i<=90;i++){
        if(f[i]>0){
            n++;a[n]=i;
        }
    }
    ff(n/2,1,n/2,nc1,c1);
    ff(n-n/2,n/2+1,n,nc2,c2);

    nrsol=0;
    for(i=1,j=nc2;i<=nc1;i++){
        while(j>=1 && c2[j].s+c1[i].s>0){j--;}
        j1=j;
        while(j1>=1 && c2[j1].s+c1[i].s==0){j1--;}
        i1=i;
        while(i1<=nc1 && c1[i1].s==c1[i].s){i1++;}
        for(l=j1+1;l<=j;l++){
            for(k=i;k<=i1-1;k++){
                if((c2[l].v & c1[k].v) == 0){
                    nrsol=nrsol+c2[l].c*c1[k].c;
                }
            }
        }
        i=i1-1;  j=j1;
    }
    fout<<nrsol<<"\n";
    fout.close(); fin.close(); return 0;
}



