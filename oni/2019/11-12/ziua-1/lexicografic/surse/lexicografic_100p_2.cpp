#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;
#define SZ(x) ((int) (x).size())

const int INF = 0x3f3f3f3f;

class SegmentTree {
public:
    SegmentTree(const vector<int>& m):
        sum(SZ(m) * 4 + 5), vmin(SZ(m) * 4 + 5), n(SZ(m)) {
            build(0, 0, n - 1, m);
        }
    pair<int, int> getMin(int lim) {
        return getMin(0, 0, n - 1, lim);
    }
    int remove(int pos) {
        return remove(0, 0, n - 1, pos);
    }

private:
    vector<int> sum;
    vector<pair<int, int>> vmin;
    int n;

    void build(int node, int left, int right, const vector<int>& m) {
        sum[node] = right - left + 1;
        if (left == right) {
            vmin[node] = make_pair(m[left], left);
        } else {
            int mid = (left + right) / 2;
            build(2 * node + 1, left, mid, m);
            build(2 * node + 2, mid + 1, right, m);
            vmin[node] = min(vmin[2 * node + 1], vmin[2 * node + 2]);
        }
    }

    pair<int, int> getMin(int node, int left, int right, int lim) {
        if (sum[node] <= lim) {
            return vmin[node];
        } else {
            int mid = (left + right) / 2;
            auto ret = getMin(2 * node + 1, left, mid, lim);
            if (lim > sum[2 * node + 1]) {
                ret = min(ret, getMin(2 * node + 2,
                            mid + 1, right, lim - sum[2 * node + 1]));
            }
            return ret;
        }
    }
    int remove(int node, int left, int right, int pos) {
        if (left == right) {
            vmin[node] = make_pair(INF, INF);
            sum[node] = 0;
            return 0;
        } else {
            int mid = (left + right) / 2;
            int ret;
            if (pos <= mid) {
                ret = remove(2 * node + 1, left, mid, pos);
            } else {
                ret = remove(2 * node + 2, mid + 1, right, pos);
                ret += sum[2 * node + 1];
            }
            sum[node] = (sum[2 * node + 1] + sum[2 * node + 2]);
            vmin[node] = min(vmin[2 * node + 1], vmin[2 * node + 2]);
            return ret;
        }
    }
};

int main() {
    ifstream fin("lexicografic.in");
    ofstream fout("lexicografic.out");

    int T;
    fin >> T;

    while (T-- > 0) {
        int n;
        int64_t k;
        fin >> n >> k;

        vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            fin >> numbers[i];
        }

        SegmentTree t(numbers);
        for (int i = 0; i < n; ++i) {
            auto vmin = t.getMin((int) min(k + 1, (int64_t) n));
            fout << vmin.first << ' ';
            k -= t.remove(vmin.second);
        }

        fin.close();
        fout.close();
    }
}
