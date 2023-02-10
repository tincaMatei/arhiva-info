///complexitate O(N*(2^N))
#include<fstream>
using namespace std;
ifstream fin ("scara.in");
ofstream fout("scara.out");
int N, i, a[1005], b[1005];
void sol2(){
    int i,nb,pr,x;
    nb=0;pr=N;
    while(nb<N){
        x=a[pr];
        a[pr]=0;
        pr--;
        i=1;
        while(b[i]!=0){
            pr++;
            a[pr]=b[i];
            b[i]=0;
            i++;
            nb--;
        }
        b[i]=x;
        nb++;
    }
}
int main(){
    fin>>N;
    for(i=1;i<=N;i++){
        fin>>a[i];
    }
    sol2();
    for(i=1;i<=N;i++)fout<<b[i]<<" ";
    fout<<"\n"; fout.close(); fin.close();
    return 0;
}
