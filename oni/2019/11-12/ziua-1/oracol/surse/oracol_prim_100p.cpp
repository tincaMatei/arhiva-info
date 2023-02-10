#include <fstream>
#include <vector>
#include <limits>
#include <iterator>
#include <numeric>
using namespace std;

int64_t SpanningTree(const vector<vector<int>>& cost) {
	int n = static_cast<int>(cost.size());
	vector<int> prim_cost(n);
	vector<int> available(n);
	iota(available.begin(), available.end(), 0);
	fill(next(prim_cost.begin()), prim_cost.end(), 
			numeric_limits<int>::max());
	int64_t total = 0;
	for (int i = 0; i < n; ++i) {
		int best_node = 0;
		for (int j = 1; j < static_cast<int>(available.size()); ++j) {
			if (prim_cost[available[j]] < prim_cost[available[best_node]]) {
				best_node = j;
			}
		}
		
		int extracted_node = available[best_node];
		total += prim_cost[extracted_node];
		
		swap(available[best_node], available.back());
		available.pop_back();
		
		for (auto&& node: available) {
			if (cost[extracted_node][node] < prim_cost[node]) {
				prim_cost[node] = cost[extracted_node][node];
			}
		}
	}
	return total;
}

int main() {
	ifstream fin("oracol.in");
	int n; fin >> n;
	vector<vector<int>> cost(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			fin >> cost[i - 1][j];
			cost[j][i - 1] = cost[i - 1][j];
		}
	}
	ofstream("oracol.out") << SpanningTree(cost) << endl;
}