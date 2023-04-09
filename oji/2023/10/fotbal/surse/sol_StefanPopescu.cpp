// Solution stud. Stefan Popescu, Universitatea Bucuresti
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

const int nmax = 1e5;
const int mod = 1e9 + 9;
int n, k;

struct ev{
    int pos;
    bool val, pic;
}; /// pozitia la care se proceseaza, tipul de eveniment (intrare/iesire), picior (stangaci/dreptaci)

ev events[2 * nmax + 1];

bool cmp(const ev & s1, const ev & s2){
    if(s1.pos == s2.pos) /// daca lucram cu aceeasi pozitie
        return s1.val < s2.val; /// vrem ca evenimentele de iesire sa fie ultimele
    return s1.pos < s2.pos; /// daca avem pozitii diferite, vrem sa procesam mai intai evenimentele apropiate
}

int nrPic[2];
long long perm[nmax + 2];

void preCalc(){
    perm[0] = perm[1] = 1;
    for(int i = 2; i <= nmax; i++)
        perm[i] = perm[i - 1] * i % mod;
}

long long invMod(long long x){
    long long p = 1;
    int put = mod - 2;
    while(put){
        if(put & 1)
            p = p * x % mod;
        x = x * x % mod;
        put >>= 1;
    }
    return p;
}

long long getComb(int n, int k){
    if (n < k)
        return 0;
    return perm[n] * invMod(perm[n - k] * perm[k] % mod) % mod;
}
long long ans = 0;
int main(){
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    preCalc();
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        int x, y, z;
        cin >> x >> y >> z;
        events[2 * i - 2] = {x, false, (bool)z};
        events[2 * i - 1] = {y, true, (bool)z};
    }
    sort(events, events + 2 * n, cmp);
    for(int e = 0; e < 2 * n; e++){
        if(events[e].val == false){ /// intrare
            nrPic[events[e].pic]++;
        }
        else{ /// iesire
            nrPic[events[e].pic]--;
            ans = (ans + getComb(nrPic[0] + nrPic[1], k - 1) + mod - getComb(nrPic[events[e].pic], k - 1)) % mod;
        }
    }
    cout << ans << "\n";
    return 0;
}