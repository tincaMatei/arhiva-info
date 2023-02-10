#include <bits/stdc++.h>
using namespace std;

ifstream f("amat.in");
ofstream g("amat.out");

struct submatrix {
    int x1, y1, x2, y2;
    int k;
}ap[2003];
struct qry{
    int x1, y1, x2, y2, w;
} Q[100001];

const int NM = 1002;
int a[NM][NM], A[NM][NM];
int B[NM][NM];
int n, m, q, c, K;

bool verif(int nr)
{
    int x1, y1, x2, y2, w, x;

    memset(A, 0, sizeof(A));

    for(int i = 1; i <= nr; ++i){
        x1 = Q[i].x1; y1 = Q[i].y1;
        x2 = Q[i].x2; y2 = Q[i].y2;
        w = Q[i].w;
        A[x1][y1] += w;
        A[x1][y2 + 1] -= w;
        A[x2 + 1][y1] -= w;
        A[x2 + 1][y2 + 1] += w;
    }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
               A[i][j] = A[i][j] + A[i-1][j] + A[i][j-1] - A[i-1][j-1];
               x = A[i][j] + a[i][j];
               if (x < K) return 0;
            }
    return 1;
}

int main()
{
    int i, j, x, x1, y1, x2, y2;

    f >> c >> n >> m;
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            f >> a[i][j];

    if (c == 1){
        for(i = 0; i <= 2000; ++i)
            ap[i].y1 = ap[i].x1 = 2003;

        for(i = 1; i <= n; ++i)
            for(j = 1; j <= m; ++j) {
                x = a[i][j];
                x += 1000;
                ap[x].x1 = min(ap[x].x1, i);
                ap[x].y1 = min(ap[x].y1, j);
                ap[x].x2 = max(ap[x].x2, i);
                ap[x].y2 = max(ap[x].y2, j);
                ap[x].k++;
            }

        int Max_arie = 0;
        for(i = 0; i <= 2000; ++i)
            if (ap[i].k > Max_arie) {
                Max_arie = ap[i].k;
                x1 = ap[i].x1;
                x2 = ap[i].x2;
                y1 = ap[i].y1;
                y2 = ap[i].y2;
            } else if (ap[i].k == Max_arie) {
                if (ap[i].x1 > x1 || ap[i].x1 == x1 && ap[i].y1 > y1) {
                    x1 = ap[i].x1;
                    x2 = ap[i].x2;
                    y1 = ap[i].y1;
                    y2 = ap[i].y2;
                }
            }

        g << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";

    } else {

        f >> q >> K;
        for(i = 1; i <= q; ++i) {
            f >> x1 >> y1 >> x2 >> y2 >> x;
            Q[i] = {x1, y1, x2, y2, x};
        }

        i = 1, j = q;
        while (i <= j) {
            int mij = (i+j) >> 1;
            int k = verif(mij);
            if (k) j = mij - 1;
              else i = mij + 1;
        }

        g << i << "\n";
    }
    return 0;
}
