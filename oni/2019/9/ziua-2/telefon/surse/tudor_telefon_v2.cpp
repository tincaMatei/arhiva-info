#include <bits/stdc++.h>
using namespace std;
#define int long long
ifstream fin("telefon.in");
ofstream fout("telefon.out");

int n, b, i, x, y, total;
vector<int> d, signals;

void subtask() {
    int ls = 0, ld = 0, best = 0, saved = 0;
    while (ld < d.size() && d[ld] <= b) {
        saved += d[ld++];
        while ( (ld - ls) * d[ld - 1] > b ) saved -= d[ls++];

        best = max(best, saved);
    }

    fout << total - best << ' ';
}

void solve() {
    int ls = 0, ld = 0, split = 0, bonus[3], saved = 0, best = 0;

    for (int k = 0 ; k < signals.size() ; k++) {
        int signalSize = signals[k];

        while (ld < d.size() && d[ld] <= signals[k]) ld++; /// Fixate ld
        ls = max(0LL, ld - (b / signals[k])); /// Fixate ls

        split = ld + 1;
        while (split < d.size() && d[split] <= 2 * signals[k]) split++; /// Fixate split

        bonus[0] = bonus[1] = 0;
        if (split > 0 && ld != d.size()) {
            bonus[0] = min(signals[k], d[split - 1]);
            bonus[1] = max(d[split - 1] - signals[k], 0LL);
            if (bonus[1] > signalSize) bonus[1] = 0;
        }

        saved = 0;
        int spaceLeft = b / signalSize - (ld - ls);
        if (spaceLeft <= 0) {
            for (int r = ls ; r < ld ; r++) {
                if (r - ls == 0 || r - ls == 1)
                    saved += (bonus[r - ls] > d[r] ? bonus[r - ls] : d[r]);
                else
                    saved += d[r];
            }
        } else if (spaceLeft == 1) {
            for (int r = ls ; r < ld ; r++) {
                if (r - ls == 0)
                    saved += (bonus[1] > d[r] ? bonus[1] : d[r]);
                else
                    saved += d[r];
            }
            saved += bonus[0];
        } else {
            for (int r = ls ; r < ld ; r++)
                saved += d[r];
            saved += bonus[0] + bonus[1];
        }

        best = max(best, saved);
    }

    fout << total - best;
}

int32_t main()
{
    fin >> n >> b;
    fin >> x;
    for (i = 2 ; i <= n ; i++) {
        fin >> y;
        d.push_back(y - x);
        total += y - x;

        x = y;
    }
    sort(d.begin(), d.end());
    for (i = 0 ; i < d.size() ; i++) {
        cout << d[i] << ' ';
    }

    for (i = 1 ; i <= sqrt(b) ; i++)
        signals.push_back(i);
    for (i = int32_t(sqrt(b)) ; i >= 1 ; i--)
        signals.push_back(b / i);

    subtask();
    solve();

    return 0;
}
