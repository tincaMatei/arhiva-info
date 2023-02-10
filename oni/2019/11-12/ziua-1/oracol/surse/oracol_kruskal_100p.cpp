#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int from, to, cost;
    bool operator<(const Edge& e) const {
        return cost < e.cost;
    }
};

class DSU {
public:
    DSU(int n):
        f(n) {
        for (int i = 0; i < n; ++i) {
            f[i] = i;
        }
    }

    int& operator[](int x) {
        int y, p;
        for (y = x; y != f[y]; y = f[y]);
        for (; x != y; x = p) {
            p = f[x];
            f[x] = y;
        }
        return f[y];
    }
private:
    vector<int> f;
};

int main() {
    ifstream fin("oracol.in");
    ofstream fout("oracol.out");

    int n;
    fin >> n;

    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int cost;
            fin >> cost;
            edges.push_back(Edge{i, j, cost});
        }
    }
    sort(edges.begin(), edges.end());
    DSU f(n + 1);
    int64_t ans = 0;
    for (const Edge& e: edges) {
        if (f[e.from] != f[e.to]) {
            ans += e.cost;
            f[e.from] = f[e.to];
        }
    }
    fout << ans << '\n';
}

