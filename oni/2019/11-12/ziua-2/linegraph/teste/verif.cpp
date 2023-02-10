#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;

// Approved grader output format
void result(const char * msg, int p) {
    printf("%d %s", p, msg);
    exit(0);
}

void Assert(bool cond, string str) {
    if (!cond) {
        result(str.c_str(), 0);
    }
}
void Success(int pct, string str) {
    result(str.c_str(), pct);
}

ifstream fin("linegraph.in");
// Open our output
ifstream fok("linegraph.ok");
// Open their output
ifstream fout("linegraph.out");

using Tree = vector <pair <int, int> >;
using AdjList = vector <vector <int> >;

// For fast tree isomorphism
map <vector <int>, int> Map;
int dfs_get_encoding(const AdjList &tree, int node, int father, bool sudden_death) {
    vector <int> encs;
    for (const auto it: tree[node]) {
        if (it != father) {
            const int val = dfs_get_encoding(tree, it, node, sudden_death);
            if (val < 0) {
                return -1;
            }
            encs.push_back(val);
        }
    }
    sort(encs.begin(), encs.end());
    if (!Map.count(encs)) {
        if (sudden_death) {
            return -1;
        }
        int sz = Map.size();
        Map[encs] = sz;
    }
    return Map[encs];
}

int get_encoding(const Tree &t, int node, bool sudden_death) {
    // Build graph
    const int N = t.size() + 1;
    AdjList graph(N, vector <int>());
    for (const auto &it: t) {
        int a, b; tie(a, b) = it;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    return dfs_get_encoding(graph, node, -1, sudden_death);
}

bool is_tree(const Tree &t) {
    // Build graph
    // Here t DOESN'T have parallel edges nor self loops!
    const int N = t.size() + 1;
    AdjList graph(N, vector <int>());
    for (const auto &it: t) {
        int a, b; tie(a, b) = it;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Check cycleless property
    vector <bool> vis(N);
    bool failed = false;
    function <void(int, int)> dfs = [&](int node, int father) {
        vis[node] = true;
        for (const auto &it: graph[node]) {
            if (it != father) {
                if (vis[it]) {
                    failed = true;
                }
                dfs(it, node);
                if (failed) {
                    break;
                }
            }
        }
    };
    dfs(0, -1);
    return !failed;
}

void check_test() {
    Map.clear(); // Very important, watch out!

    // Read "DA/NU"
    string our_answer;
    if (!(fok >> our_answer)) Assert(false, "OK corrupted!");
    string their_answer;
    if (!(fout >> their_answer)) Assert(false, "Output file corrupted!");
    Assert(our_answer == their_answer, "Answers differ!");
    
    // Read our tree
    Tree t_ours;
    int N_ours;
    if (our_answer == "DA") {
        if (!(fok >> N_ours)) Assert(false, "OK corrupted!");
        t_ours.resize(N_ours - 1);
        for (int i = 0; i < N_ours - 1; ++i) {
            int a, b;
            if (!(fok >> a >> b)) Assert(false, "OK corrupted!");
            --a, --b; // Different encoding
            Assert(a != b, "OK doesn't contain a tree!");
            if (a > b) {
                swap(a, b);
            }
            t_ours[i] = make_pair(a, b);
        }
        // Check for repeated edges
        sort(t_ours.begin(), t_ours.end());
        t_ours.resize(unique(t_ours.begin(), t_ours.end()) - t_ours.begin());
        Assert(t_ours.size() == N_ours - 1, "OK doesn't contain a tree!");
        // Check OK is a tree
        Assert(is_tree(t_ours), "OK doesn't contain a tree!");
    }

    // Read their answer tree
    Tree t_theirs;
    int N_theirs;
    if (their_answer == "DA") {
        if (!(fout >> N_theirs)) Assert(false, "Output file corrupted!");
        Assert(N_ours == N_theirs, "Wrong answer!");
        t_theirs.resize(N_theirs - 1);
        for (int i = 0; i < N_theirs - 1; ++i) {
            int a, b;
            if (!(fout >> a >> b)) Assert(false, "Output file corrupted!");
            --a, --b; // Different encoding
            Assert(a != b, "Output file doesn't contain a tree!");
            if (a > b) {
                swap(a, b);
            }
            t_theirs[i] = make_pair(a, b);
        }
        // Check for repeated edges
        sort(t_theirs.begin(), t_theirs.end());
        t_theirs.resize(unique(t_theirs.begin(), t_theirs.end()) - t_theirs.begin());
        Assert(t_theirs.size() == N_theirs - 1, "Output file doesn't contain a tree!");
        // Check Output is a tree
        Assert(is_tree(t_theirs), "Output file doesn't contain a tree!");
    }

    // Attempt to fix
    if (their_answer == "DA") {
        const auto our_encoding = get_encoding(t_ours, 0, false);
        assert(our_encoding != -1);
        for (int root = 0; root < N_ours; ++root) {
            const auto their_encoding = get_encoding(t_theirs, root, true);
            if (our_encoding == their_encoding) {
                return ; // Fine, go on
            }
        }
        Assert(false, "Wrong answer!");
    }
}

int main() {
    int T = 0;
    if (!(fin >> T)) Assert(false, "Input Corrupted!");
    int scor = 0;
    if (!(fok >> scor)) Assert(false, "OK corrupted!");
    for (int t = 1; t <= T; ++t) {
        check_test();
    }
    Success(scor, "OK!");
    return 0;
}