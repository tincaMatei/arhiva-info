// student Lucian Bicsi - Universitatea din Bucuresti - 100 puncte

#include <bits/stdc++.h>

using namespace std;

struct Prog {
    long long a, r, n;
};

long long gcd(long long a, long long b) {
    while (b) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

Prog Merge(Prog p1, Prog p2) {
    if (p1.n == 0) return p1;
    long long new_r = p1.r * p2.r / gcd(p1.r, p2.r);
    for (int i = 0; i < p2.a + p2.r && i < p1.n; ++i) {
        long long x = p1.a + p1.r * i;
        x -= p2.a;
        if (x % p2.r == 0) {
            x /= p2.r;
            if (x >= 0 && x < p2.n) {
                long long maxx = min(p1.a + p1.r * (p1.n - 1),
                        p2.a + p2.r * (p2.n - 1));
                maxx -= p1.a + p1.r * i;
                if (maxx < 0) break;
                maxx /= new_r;
                return {p1.a + p1.r * i, new_r, maxx + 1};
            }
        }
    }
    return {0, 0, 0};
}

ostream& operator<<(ostream& out, Prog prog) {
    out << "(" << prog.a << " + " << prog.r << " x " << prog.n << ")";
    return out;
};

long long Calc(vector<Prog> progs) {
    // for (auto x : progs) cerr << x << " ";
    Prog ret{0, 1, (long long)2e18};
    for (auto prog : progs) {
        ret = Merge(ret, prog);
    }
    // cerr << " -> " << ret << endl;
    return ret.n;
}

int main() {
    ifstream cin("pro3.in");
    ofstream cout("pro3.out");
    auto read = [&]() {
        Prog ret;
        cin >> ret.a >> ret.r >> ret.n;
        return ret;
    };
    Prog a = read(), b = read(), c = read();
    cout << Calc({a}) + Calc({b}) + Calc({c}) - 
        Calc({a, b}) - Calc({a, c}) - Calc({b, c})
        + Calc({a, b, c}) << endl;
    return 0;
}
