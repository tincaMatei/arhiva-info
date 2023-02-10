// O(N*M)
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 502
#define INF      1000000000
char a[MAX_SIZE][MAX_SIZE];
int  w[MAX_SIZE][MAX_SIZE], e[MAX_SIZE][MAX_SIZE];
int  q[2][MAX_SIZE*MAX_SIZE];
int  dx[] = {-1, +1,  0,  0};
int  dy[] = { 0,  0, -1, +1};

void swap(int *x, int *y) {
    *x ^= *y; *y ^= *x; *x ^= *y;
}

void bestTimeFrom(int x, int y, char a[][MAX_SIZE], int n, int m, int t, int d[][MAX_SIZE]) {
    int beg[]   = {0, 0};
    int end[]   = {0, 0};
    int delay[] = {0, t};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            d[i][j] = INF;

    q[0][end[0]++] = x*m + y; d[x][y] = 0;
    for (int now = 0; beg[0] < end[0] || beg[1] < end[1]; now++) {
        if (beg[0] == end[0]) {
            int v = q[1][beg[1]]; x = v / m; y = v % m;
            now = d[x][y] + delay[1];
        }

        for (int i = 0; i < 2; i++) {
            for (; beg[i] < end[i]; beg[i]++) {
                int v = q[i][beg[i]]; x = v / m; y = v % m;
                if (d[x][y] + delay[i] > now) break;
                for (int k = 0; k < 4; k++) {
                    int r = x + dx[k], c = y + dy[k];
                    if (d[r][c] == INF && a[r][c] != '#') {
                        d[r][c] = now + 1;
                        if (a[r][c] == '.') q[0][end[0]++] = r*m + c;
                        if (a[r][c] == '+') q[1][end[1]++] = r*m + c;
                    }
                }
            }
        }
    }
}

void tryWithOnePortal(char a[][MAX_SIZE], int w[][MAX_SIZE], int e[][MAX_SIZE], int n, int m, int *ans, int *m1, int *m2) {
    int x1 = -1, x2 = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == 'P') {
                int x3 = e[i][j];
                if (x3 > x2) swap(&x3, &x2);
                if (x2 > x1) swap(&x2, &x1);
            }
    *m1 = x1; *m2 = x2;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == 'P') {
                int d = (e[i][j] == x1) ? x2 : x1;
                if (w[i][j] + d < *ans) *ans = w[i][j] + d;
            }
}

int reuse(int x, int y, char a[][MAX_SIZE], int t) {
    int cost = INF;
    for (int k = 0; k < 4; k++) {
        int r = x + dx[k], c = y + dy[k];
        if (a[r][c] == '.') return 2;
        if (a[r][c] == '+') cost = t + 2;
    }
    return cost;
}

int main() {
    FILE    *f = fopen("walle.in",  "r");
    FILE    *g = fopen("walle.out", "w");
    int     n, m, t, wx, wy, ex, ey, m1, m2;

    fscanf(f, "%d %d %d", &n, &m, &t);
    memset(a[0], '#', m + 2);
    for (int i = 1; i <= n; i++) {
        a[i][0] = '#'; fscanf(f, "%s", &a[i][1]); a[i][m + 1] = '#';
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'W') a[i][j] = '.', wx = i, wy = j;
            if (a[i][j] == 'E') a[i][j] = '.', ex = i, ey = j;
        }
    }
    memset(a[n + 1], '#', m + 2);
    n += 2; m += 2;

    bestTimeFrom(wx, wy, a, n, m, t, w);
    bestTimeFrom(ex, ey, a, n, m, t, e);

    int ans = w[ex][ey];
    tryWithOnePortal(a, w, e, n, m, &ans, &m1, &m2);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == 'P') {
                int d = reuse(i, j, a, t) + ((e[i][j] == m1) ? m2 : m1);
                if (e[i][j] > d) e[i][j] = d;
            }

    tryWithOnePortal(a, w, e, n, m, &ans, &m1, &m2);
    fprintf(g, "%d", (ans != INF) ? ans : -1);

    fclose(f);
    fclose(g);

    return 0;
}

