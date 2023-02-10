#include <fstream>
using namespace std;
ifstream in("scara.in");
ofstream out("scara.out");
int n,x[10001],ff[10001],f[10001];
int main(){
    in>>n;
    for(int i=1;i<=n;i++){in>>x[i];}
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){ff[j]=f[j];}
        for(int j=1;j<i;j++){f[j]=ff[ff[j]]+1;}
        f[i]=1;}
    out<<x[f[1]];
    for(int i=2;i<=n;i++){
        out<<' '<<x[f[i]];}
    out<<'\n';
    return 0;
}
