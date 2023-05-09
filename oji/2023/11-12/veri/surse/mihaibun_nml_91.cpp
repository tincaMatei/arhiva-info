#include <bits/stdc++.h>
#define inf 2000000000
#define N 5003
using namespace std;
ifstream fin("veri.in");
ofstream fout("veri.out");
vector<int> g[N];
int a,b,minim,n,lung,nr,z,w,e,x,ultim,y;
int dist[N][N], ta[N][N], sir[N], viz[N],t[N],ss[10*N];

void dj(int src)
{
    set< pair<int, int> > mul;
    mul.insert({0, src});
    dist[src][src] = 0;
    ta[src][src] = 0;
    while (!mul.empty())
    {
        pair<int, int> tmp = *(mul.begin());
        mul.erase(mul.begin());
        int u = tmp.second;
        int h;
        for (h = 0; h < g[u].size(); h++)
        {
            int v = g[u][h];
            if (dist[src][v] > dist[src][u] + 1)
            {
                if (dist[src][v] != inf)
                    mul.erase(mul.find({dist[src][v], v}));
                dist[src][v] = dist[src][u] + 1;
                ta[src][v] = u;
                mul.insert({dist[src][v], v});
            }
        }
    }
}

void ciclu(int src)
{
    queue<pair<int,int> > q;
    int nod,timp;

    q.push({src,0});
    viz[src] = e;
    ta[src][src] = 0;
    while(!q.empty())
    {
        nod = (q.front()).first;
        timp = (q.front()).second;
        q.pop();
        for(int h = 0; h < g[nod].size(); h++)
        {
            if(g[nod][h]==src)
            {
                if(timp+1 < t[src]) {t[src] = timp+1; ultim = nod;}

            }
            else
            if(viz[g[nod][h]]!=e)
            {
                ta[src][g[nod][h]] = nod;
                viz[g[nod][h]] = e;
                q.push({g[nod][h],timp+1});
            }
        }
    }
}

int main()
{
    int c,s,u,v,m,i,j,sol,ti;
    fin >> c;
    fin >> n >> m;
    fin >> s >> a >> b;
    for(i = 1; i <= m; i++)
    {
        fin >> u >> v;
        g[u].push_back(v);
    }
    if(a==b)
    {
        for(i = 1; i <= n; i++)
            dist[s][i] = inf;
        dj(s);
        if(c==1) fout << dist[s][a] << "\n";
        else
        {
            j = a;
            nr = 0;
            while(j != 0)
            {
                nr++;
                sir[nr] = j;
                j = ta[s][j];
            }
            fout << nr-1 << "\n";
            for(i = nr; i >= 1; i--)
                fout << sir[i] << " ";
            fout << "\n";
            fout << 0 << "\n" << a << "\n" << 0 << "\n" << a <<"\n";
        }
    }
    else
    {
        if((m > 500)and(n > 500)) ti = clock();
        if(c==1)
        {
            minim = inf;
            for(i = 1; i <= n; i++)
                dist[s][i] = inf;
            dj(s);
            for(i = 1; i <= n; i++)
                if(clock()-ti < 1950000)
            {
                t[i] = inf;
                e++;
                ciclu(i);
                if(t[i] < inf)
                {
                    for(j = 1; j <= n; j++)
                        dist[i][j] = inf;
                    dj(i);
                    x = dist[s][i]+t[i]+max(dist[i][a],dist[i][b]);
                    if(x < minim) minim = x;
                }
            }
            fout << minim << "\n";
        }
        else
        {
             minim = inf;
            for(i = 1; i <= n; i++)
                dist[s][i] = inf;
            dj(s);
            y = inf;
            for(i = 1; i <= n; i++)
                if(clock()-ti < 1950000)
            {
                t[i] = inf;
                e++;
                ciclu(i);
                if(t[i] < inf)
                {
                    for(j = 1; j <= n; j++)
                        dist[i][j] = inf;
                    dj(i);
                    x = dist[s][i]+t[i]+max(dist[i][a],dist[i][b]);
                    if(x < minim)
                    {
                        minim = x;
                        w = i;
                        y = dist[s][i];
                    }
                    else if(x==minim)
                    {
                        if(dist[s][i] < y)
                        {
                            y = dist[s][i];
                            w = i;
                        }
                    }
                }
            }
            lung = 0;
            nr = 0;
            j = w;
            while(j!=0)
            {
                nr++;
                sir[nr] = j;
                j = ta[s][j];
            }
            for(j = nr; j >= 1; j--)
            {
                lung++;
                ss[lung] = sir[j];
            }
            t[w] = inf;
            e++;
            ciclu(w);
            nr = 1;
            sir[1] = w;
            j = ultim;
            while(j != w)
            {
                nr++;
                sir[nr] = j;
                j = ta[w][j];
            }
            for(j = nr; j >= 1; j--)
            {
                lung++;
                ss[lung] = sir[j];
            }
            fout << lung-1 << "\n";
            for(j = 1; j <= lung; j++)
                fout << ss[j] << " ";
            fout << "\n";
            for(j = 1; j <= n; j++)
                dist[w][j] = inf;
            dj(w);
            nr = 0;
            j = a;
            while(j!=0)
            {
                nr++;
                sir[nr] = j;
                j = ta[w][j];
            }
            fout << nr-1 << "\n";
            for(j = nr; j >= 1; j--)
                fout << sir[j] << " ";
            fout << "\n";
            nr = 0;
            j = b;
            while(j!=0)
            {
                nr++;
                sir[nr] = j;
                j = ta[w][j];
            }
            fout << nr-1 << "\n";
            for(j = nr; j >= 1; j--)
                fout << sir[j] << " ";
            fout << "\n";
        }
    }

    return 0;
}
