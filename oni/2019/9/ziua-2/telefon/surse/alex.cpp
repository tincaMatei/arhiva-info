#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
vector<long long> v,dist,vals;
long long total,n,m,current,best,nokid;
int32_t main()
{
    ifstream cin("telefon.in");
    ofstream cout("telefon.out");
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        v.push_back(a);
    }
    for(int i = 0; i < v.size() - 1; i++)
    {
        dist.push_back(v[i + 1] - v[i]);
        vals.push_back(v[i + 1] - v[i]);
        total += v[i + 1] - v[i];
    }

    sort(dist.begin(), dist.end());
    int i;
    for(i = 1; i*i <= m; i++)
        vals.push_back(i),vals.push_back(m/i);
    vals.push_back(i), vals.push_back(i + 1);

    sort(vals.begin(), vals.end());

    int first = 0;
    int semnal = 0;
    int second = 0;
    int extra = 0;
    current = dist[0];
    while(first < dist.size())
    {
        while(semnal + 1 < vals.size() && vals[semnal] < dist[first])
            semnal++;
        if(vals[semnal] < dist[first])
            break;
        long long delta = vals[semnal];
        while((first - second + 1) * delta > m)
            current -= dist[second], second++;
        while(extra + 1 < dist.size() && dist[extra + 1] - delta <= delta)
            extra++;
        if(extra == first && extra + 1 < dist.size())
            extra++;
        int aux = second;
        long long size = (first-second+1) * delta;
        if(extra != first)
        {
            long long z = current;
            long long plus = dist[extra] - delta;

            if(size + delta <= m)
                size += delta, z += delta;
            else if(aux <= first)
                z += delta - dist[aux], aux++;

            if(size + delta <= m)
                size += plus, z += delta;
            else if(aux <= first && dist[aux] < plus)
                z += plus - dist[aux];
            best = max(z, best);
        }
        nokid = max(current, nokid);
        best = max(current, best);
        if(first + 1 == dist.size())
            first++;
        else
        if(semnal + 1 < vals.size() && vals[semnal + 1] < dist[first + 1])
            semnal++;
        else
            first++,current+= dist[first];
    }
    long long z = 0;
    cout<<max(z,total-nokid) << ' ';
    cout<<max(z,total-best) << '\n';
}
