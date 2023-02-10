#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 30;
const int NMAX = 250005;

int t, n, a[NMAX];
int aint_mn[4 * NMAX], aint_sum[4 * NMAX];
long long k;

void Update_sum(int node, int st, int dr, int poz, int val)
{
    if (st == dr)
        aint_sum[node] = val;
    else
        {
            int mij = (st + dr) / 2;
            if (poz <= mij) Update_sum(2 * node, st, mij, poz, val);
            if (poz > mij) Update_sum(2 * node + 1, mij + 1, dr, poz, val);
            aint_sum[node] = aint_sum[2 * node] + aint_sum[2 * node + 1];
        }    
}

void Update_mn(int node, int st, int dr, int poz, int val)
{
    if (st == dr)
        aint_mn[node] = val;
    else
        {
            int mij = (st + dr) / 2;
            if (poz <= mij) Update_mn(2 * node, st, mij, poz, val);
            if (poz > mij) Update_mn(2 * node + 1, mij + 1, dr, poz, val);
            aint_mn[node] = a[aint_mn[2 * node]] <= a[aint_mn[2 * node + 1]] ? aint_mn[2 * node] : aint_mn[2 * node + 1];
        }
}

int Query_sum(int node, int st, int dr, int l, int r)
{
    if (l <= st && dr <= r)
        return aint_sum[node];
    else
        {
            int mij = (st + dr) / 2, val = 0;
            if (l <= mij) val += Query_sum(2 * node, st, mij, l, r);
            if (r > mij) val += Query_sum(2 * node + 1, mij + 1, dr, l, r);
            
            return val;
        }
}

int Query_poz(int node, int st, int dr, long long many)
{
    if (st == dr)
        return st;
    else
    {
        int mij = (st + dr) / 2;
        if (aint_sum[2 * node] >= many)
            return Query_poz(2 * node, st, mij, many);
        else 
            return Query_poz(2 * node + 1, mij + 1, dr, many - aint_sum[2 * node]);
    }
}

int Query_mn(int node, int st, int dr, int l, int r)
{
    if (l <= st && dr <= r)
        return aint_mn[node];
    else
        {
            int mij = (st + dr) / 2, val = 0;
            if (l <= mij) 
            {
                int ans = Query_mn(2 * node, st, mij, l, r);
                val = a[val] <= a[ans] ? val : ans;
            }
            if (r > mij) 
            {
                int ans = Query_mn(2 * node + 1, mij + 1, dr, l, r);
                val = a[val] <= a[ans] ? val : ans;
            }
                
            return val;
        }
}

    
int main()
{
    freopen("lexicografic.in", "r", stdin);
    freopen("lexicografic.out", "w", stdout);
    cin.sync_with_stdio(false);

    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        a[0] = inf;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            Update_sum(1, 1, n, i, 1);
            Update_mn(1, 1, n, i, i);
        }
        
        for (int i = 1; i <= n; i++)
        {
            // find k + 1 unvisited
            int poz = Query_poz(1, 1, n, k + 1);

            // take min from [1, poz]
            int mn_poz = Query_mn(1, 1, n, 1, poz);

            // mark it as visited
            cout << a[mn_poz] << " ";
            k -= Query_sum(1, 1, n, 1, mn_poz) - 1;
            Update_sum(1, 1, n, mn_poz, 0);
            Update_mn(1, 1, n, mn_poz, 0);
        }

        cout << "\n";


        // clear
        for (int i = 1; i <= n * 4; i++)
            aint_mn[i] = aint_sum[i] = 0;
    }
    return 0;
}