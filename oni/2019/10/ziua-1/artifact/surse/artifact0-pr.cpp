///ecuatie de forma v[1]*c[1]+v[2]*c[2]+...+v[10]*c[10]
///generare de aranjamente de 10 luate cate n
#include<fstream>
#include<string.h>
using namespace std;
ifstream fin ("artifact.in");
ofstream fout("artifact.out");
long long N,M,i,j, p[92],a[12],c[92],d[92],v[22],f[92], n,k,l,x,q,nrsol,ok,ok1,s,r,y;
///a[] contine codurile ASCII ale literelor implicate
///p[j]=1 daca litera j este pe prima pozitie
///p[j]=0 in caz contrar
///n=numarul literelor implicate
///v[i] este valoarea temporar asociata cu litera a[i]
///c[j] este coeficientul din ecuatie asociat literei j
char t[12];
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
    ///va trebui sa asociem literelor j valorile v[j] astfel incat suma coeficientilor c[j] asociati sa fie nula
    nrsol=0;
    ///initializare
    for(i=1;i<=10;i++){
        v[i]=i-1;
    }
    r=10;///ultima pozitie ocupata in v[]
    do{
        ///verifcam ca in v[1...n] sa nu avem 0 asociat unei litere j cu p[j]=1
        ok=1;
        for(i=1;i<=n;i++){
            if(v[i]==0 && p[a[i]]==1){
                ok=0;break;
            }
        }
        if(ok==1){
            ///verificam daca avem solutie
            s=0;
            for(i=1;i<=n;i++){
                s=s+v[i]*c[a[i]];
                d[a[i]]=v[i];
            }
            if(s==0){
                nrsol++;
            }
        }
        ///trecem la urmatoarea asociere litere-cifre

        ok1=0;
        for(i=n;i>=1;i--){
            ///cautam cea mai buna inlocuire pentru v[i]
            ///de observat ca in permanenta secventa v[i+1..10] este ordonata strict crescator
            if(i+1<=10 && v[i]<v[r]){
                ///sigur gasim
                j=n+1;while(j<=r && v[i]>v[j])j++;
                x=v[i];v[i]=v[j];v[j]=x;
                for(k=n+1,j=i+1;k<=r;j++,k++){
                    v[j]=v[k];
                }
                r=j-1; ok1=1;
                break;
            }
            else{
                ///nu gasim
                r++;v[r]=v[i];
            }
        }
    }while(ok1==1);
    fout<<nrsol;
    fout.close(); fin.close(); return 0;
}

