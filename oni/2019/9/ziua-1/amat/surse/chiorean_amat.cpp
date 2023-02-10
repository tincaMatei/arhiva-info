// student Tudor Chiorean - Universitatea Tehnica din Cluj - 100 puncte


#include <bits/stdc++.h>
using namespace std;

#define NMAX 1005
#define VALMAX 1000000000
#define VALMIN -1000

ifstream fin("amat.in");
ofstream fout("amat.out");

struct query{
    int x1, y1, x2, y2, v;
};
struct subtaskAnswer{
    int x1, y1, x2, y2;
};

int n, m, i, j, q, k, c;
int mat[NMAX + 5][NMAX + 5], aux[NMAX + 5][NMAX + 5];
query queries[100000 + 5];

void DEBUG_endmatrix() {
    for (i = 1 ; i <= n ; i++) {
        for (j = 1 ; j <= m ; j++) {
            cout << aux[i][j] << ' ';
        }
        cout << '\n';
    }
}

void subtask() {
    int crt, cnt, maxCnt = 0, i, j, lin, col;
    subtaskAnswer subAns;

    for (i = 1 ; i <= n ; i++) {
        for (j = 1 ; j <= m ; j++) {
            if (aux[i][j] == 1) continue;

            crt = mat[i][j];
            cnt = 0;
            for (lin = i ; lin <= n ; lin++) {
                if (mat[lin][j] != crt) break;
                for (col = j ; col <= m ; col++) {
                    if (mat[lin][col] != crt) break;
                    aux[lin][col] = 1;

                    cnt++;
                }
            }

            if (cnt >= maxCnt) {
                subAns.x1 = i;
                subAns.y1 = j;
                subAns.x2 = lin - 1;
                subAns.y2 = col - 1;

                maxCnt = cnt;
            }
        }
    }

    fout << subAns.x1 << ' ' << subAns.y1 << ' ' << subAns.x2 << ' ' << subAns.y2 << '\n';
}

int solve(int nrQ) {
    int val;
    memset(aux, 0, sizeof(aux));

    for (i = 1 ; i <= nrQ ; i++) {
        val = queries[i].v;
        aux[queries[i].x1][queries[i].y1] += val;
        aux[queries[i].x1][queries[i].y2 + 1] += -val;
        aux[queries[i].x2 + 1][queries[i].y1] += -val;
        aux[queries[i].x2 + 1][queries[i].y2 + 1] += val;
    }

    for (i = 1 ; i <= n ; i++)
        for (j = 1 ; j <= m ; j++)
            aux[i][j] += aux[i][j - 1];

    for (j = 1 ; j <= m ; j++)
        for (i = 1 ; i <= n ; i++)
            aux[i][j] += aux[i - 1][j];

    /**
    cout << nrQ << '\n';
    DEBUG_endmatrix();
    cout << "-----------------\n";
    */

    for (i = 1 ; i <= n ; i++)
        for (j = 1 ; j <= m ; j++)
            if (aux[i][j] + mat[i][j] < k) return 0;

    return 1;
}

void maintask() {
    int ls = 1, ld = q, mij, best = q;
    while (ls <= ld) {
        mij = (ls + ld) / 2;

        if (solve(mij)) {
            best = mij;
            ld = mij - 1;
        } else {
            ls = mij + 1;
        }
    }

    fout << best;
}

int main()
{
    fin >> c;
    fin >> n >> m;

    assert(c == 1 || c == 2);
    assert(2 <= n && n <= NMAX);
    assert(2 <= m && m <= NMAX);

    for (i = 1 ; i <= n ; i++)
        for (j = 1 ; j <= m ; j++) {
            fin >> mat[i][j];

            assert(VALMIN <= mat[i][j] && mat[i][j] <= 1000);
        }
    if (c == 1) {
        subtask();
    } else {
        fin >> q >> k;
        assert(VALMIN <= k && k <= VALMAX);
        assert(1 < q && q <= 100000);
        for (i = 1 ; i <= q ; i++) {
            fin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2 >> queries[i].v;

            assert(1 <= queries[i].x1 && queries[i].x1 <= n);
            assert(1 <= queries[i].y1 && queries[i].y1 <= m);
            assert(1 <= queries[i].x2 && queries[i].x2 <= n);
            assert(1 <= queries[i].y2 && queries[i].y2 <= m);
            assert(queries[i].x1 <= queries[i].x2 && queries[i].y1 <= queries[i].y2);
        }
        maintask();
    }
    return 0;
}
