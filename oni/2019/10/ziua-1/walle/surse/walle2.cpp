///O(N*M)
#include<fstream>
#include<iostream>
#define nmax 502
#define nmax2 250002
using namespace std;
ifstream fin ("walle.in");
ofstream fout("walle.out");
int N,M,T,le,ce,lw,cw,i,j,i1,j1,i2,j2,k,ul,pr,nr,ul2,pr2,nr2,r,P,y1,y,z,dmin,de1,de2,d,d1,d2,c1,dc1;
int W[nmax][nmax],E[nmax][nmax],usi[nmax][nmax],infinit=1000000000;
int dl[4]={-1, 0,+1, 0};
int dc[4]={ 0,+1, 0,-1};
char A[nmax][nmax],ch;
struct pozitie{
    int lin,col;
}coada[nmax2],coada2[nmax2];

void solve(int X[nmax][nmax],int lx, int cx){
    int i1,j1,k,i,j;
    ul=0; pr=1; nr=0; ul2=0; pr2=1; nr2=0; r=nmax2-2;
    X[lx][cx]=0; ul++; nr++;coada[ul]={lx,cx};
    while(nr+nr2){
        if((nr==0) || (nr>0 && nr2>0 && X[coada[pr].lin][coada[pr].col]>usi[coada2[pr2].lin][coada2[pr2].col])){
            pr--; if(pr==0){pr=r;} nr++;
            coada[pr]=coada2[pr2];
            pr2++; if(pr2>r){pr2=1;} nr2--;
        }
        i1=coada[pr].lin; j1=coada[pr].col;

        for(k=0;k<=3;k++){
            i=i1+dl[k]; j=j1+dc[k];
            if(i>=1 && i<=N && j>=1 && j<=M && A[i][j]!='#' && X[i][j]==infinit){
                if(A[i1][j1]=='+'){X[i][j]=1+usi[i1][j1];}
                else {X[i][j]=1+X[i1][j1];}
                if(A[i][j]!='P' && A[i][j]!='+'){
                    ul++; if(ul>r){ul=1;} nr++;
                    coada[ul]={i,j};
                }
                if(A[i][j]=='+'){
                    usi[i][j]=T+X[i][j];
                    ul2++; if(ul2>r){ul2=1;} nr2++;
                    coada2[ul2]={i,j};
                }
            }
        }
        pr++; if(pr>r){pr=1;} nr--;
    }
}
int main(){
    fin>>N>>M>>T;
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            fin>>ch;
            A[i][j]=ch;
            if(ch=='W'){lw=i;cw=j;}
            if(ch=='E'){le=i;ce=j;}
            if(ch=='P'){P++;}
            W[i][j]=infinit; E[i][j]=infinit;
        }
    }
    ///determinam W[i][j]=numarul minim de secunde in care se poate ajunge la [i][j] pornind de la [lw][cw], fara portaluri
    solve(E,le,ce);
    ///determinam cele mai mari doua distante de la portaluri spre EXIT
    de1=0; de2=0; y=0;
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            if(A[i][j]=='P' && E[i][j]<infinit){
                y++;
                if(E[i][j]>=de1){
                    de2=de1;de1=E[i][j];i1=i;j1=j;
                }
                else{
                    if(E[i][j]>de2){de2=E[i][j];}
                }
            }
            usi[i][j]=0;
        }
    }
    solve(W,lw,cw);
    dmin=W[le][ce];
    c1=0;
    for(k=0;k<=3;k++){
        i2=i1+dl[k]; j2=j1+dc[k];
        if(i2>=1 && i2<=N && j2>=1 && j2<=M && A[i2][j2]=='.'){
            c1++;
        }
    }
    if(c1==0){dc1=2+T;}
    else {dc1=2;}
    ///imbunatatim solutia minima folosind portaluri
    ///W trebuie sa ajunga la un portal si apoi de la orice alt portal trebuie sa se poata ajunge la E
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            if(A[i][j]=='P' && W[i][j]<infinit){
                y1=y; d=E[i][j]; d2=W[i][j];
                if(d<infinit){y1--;}
                if(y1+1==P){
                    if(d==de1){d1=de2;}
                    else {d1=min(de1,d+dc1);}
                    if(dmin>d1+d2){dmin=d1+d2;}
                }
            }
        }
    }
    if(dmin==infinit){
        dmin=-1;
    }
    fout<<dmin;
    fout.close(); fin.close();
    return 0;
}

