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

    int st = 1;
    int dr = qq;
    int rasp = 0;
    while(st <= dr)
    {
        int mij = (st + dr) / 2;
        int ok = 1;
        for(int i = 1; i <= mij; i++)
            dp[q[i].x1][ q[i].y1 ] += q[i].val,
            dp[q[i].x2 + 1][ q[i].y2 + 1] += q[i].val,
            dp[q[i].x1][ q[i].y2 + 1 ] -= q[i].val,
            dp[q[i].x2 + 1][ q[i].y1] -= q[i].val;

        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
            {
                dp[i][j] += dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
                if(dp[i][j] + init[i][j] < k)
                    ok = 0;
            }

        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                dp[i][j] = 0;

        if(ok)
            rasp = mij, dr = mij - 1;
        else
            st = mij + 1;
    }
    fout << rasp << '\n';
    return 0;
}
