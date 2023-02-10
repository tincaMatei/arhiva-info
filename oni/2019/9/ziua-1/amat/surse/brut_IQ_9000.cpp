#include <iostream>
#include <fstream>
#include <assert.h>
#define x1 first.first
#define y1 first.second
#define x2 second.first
#define y2 second.second.first
#define val second.second.second
using namespace std;

ifstream fin("amat.in");
ofstream fout("amat.out");

int init[1002][1002], dp[1002][1002];
pair< pair<int,int>, pair<int, pair<int,int> > > q[250001];
int qq,k,n,m;
int bad;
int main()
{
    int optiune;
    fin >> optiune >> n >> m;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            fin >> init[i][j];

    fin >> qq >> k;

    for(int i = 1; i <= qq; i++)
        fin >> q[i].x1 >> q[i].y1 >> q[i].x2 >> q[i].y2 >> q[i].val;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(init[i][j] < k)
                bad++;
    int rasp = 0;
    for(int mij = 1; mij <= qq; mij++)
    {
        for(int i = q[mij].x1; i <= q[mij].x2; i++)
            for(int j = q[mij].y1; j <= q[mij].y2; j++){
                if(init[i][j] < k && init[i][j] + q[mij].val >= k )
                    bad--;
                init[i][j] += q[mij].val;
            }
        if(bad == 0)
        {
            fout << mij << '\n';
            return 0;
        }
    }
    return 0;
}
