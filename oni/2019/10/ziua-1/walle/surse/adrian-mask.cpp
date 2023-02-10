#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

static const int dx[4] = {-1, 0, 1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const int kInfinite = numeric_limits<int>::max() / 2;

int main() {
    ifstream cin("walle.in");
    ofstream cout("walle.out");

    int N, M, T; cin >> N >> M >> T;

    vector<string> board(N);
    for (int i = 0; i < N; ++i)
        cin >> board[i];

    pair<int, int> start, end;

    vector< pair<int, int>> portals;
    vector< vector<int> > portal_index(N, vector<int>(M, -1));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (board[i][j] == 'W')
                start = make_pair(i, j);
            else if (board[i][j] == 'E')
                end = make_pair(i, j);
            else if (board[i][j] == 'P') {
                portal_index[i][j] = portals.size();
                portals.emplace_back(i, j);
            }

    queue< pair<int, int> > normal_queue, plus_queue, portal_queue;
    int answer = numeric_limits<int>::max();
    vector<int> portal_distance(portals.size(), kInfinite);
    for (int mask = (1 << portals.size()) - 1; mask >= 0; --mask) {
        vector< vector<int> > distances(N, vector<int>(M, kInfinite));
        // distances now
        normal_queue.push(end);
        distances[end.first][end.second] = 0;

        // distances portals
        vector< pair<int, int> > temp;
        for (int i = 0; i < int(portals.size()); ++i)
            if (!((1 << i) & mask)) {
                int x, y; tie(x, y) = portals[i];
                // can still take this portal
                int now = 0;
                for (int j = 0; j < int(portals.size()); ++j)
                    if (i != j) {
                        now = max(now, portal_distance[j]);
                    }
                if (now == kInfinite)
                    continue;
                distances[x][y] = now;
                temp.emplace_back(x, y);
            }

        sort(temp.begin(), temp.end(), [&](pair<int, int> a, pair<int, int> b) {
            return distances[a.first][a.second] < distances[b.first][b.second];
        });
        for (auto &p : temp)
            portal_queue.push(p);

        while (!normal_queue.empty() || !plus_queue.empty() || !portal_queue.empty()) {
            int x = -1, y = -1;
            if (!normal_queue.empty())
                tie(x, y) = normal_queue.front();
            if (!plus_queue.empty()) {
                int x2, y2;
                tie(x2, y2) = plus_queue.front();
                if (x == -1 || distances[x][y] > distances[x2][y2]) {
                    x = x2;
                    y = y2;
                }
            }
            if (!portal_queue.empty()) {
                int x2, y2;
                tie(x2, y2) = portal_queue.front();
                if (x == -1 || distances[x][y] > distances[x2][y2]) {
                    x = x2;
                    y = y2;
                }
            }

            if (!normal_queue.empty() && make_pair(x, y) == normal_queue.front())
                normal_queue.pop();
            else if (!plus_queue.empty() && make_pair(x, y) == plus_queue.front())
                plus_queue.pop();
            else
                portal_queue.pop();

            for (int i = 0; i < 4; ++i) {
                int newx = x + dx[i];
                int newy = y + dy[i];
                if (newx < 0 || newy < 0 || newx >= N || newy >= M)
                    continue;
                if (distances[newx][newy] == kInfinite) {
                    distances[newx][newy] = distances[x][y] + 1;

                    if (board[newx][newy] == '.')
                        normal_queue.emplace(newx, newy);
                    else if (board[newx][newy] == '+') {
                        distances[newx][newy] += T;
                        plus_queue.emplace(newx, newy);
                    }
                } else if (board[newx][newy] == 'P') {
                    // might be a portal from which we starte
                    int index = portal_index[newx][newy];
                    portal_distance[index] = min(portal_distance[index], distances[x][y] + 1);
                }
            }
        }
        answer = min(answer, distances[start.first][start.second]);

        for (int i = 0; i < int(portals.size()); ++i)
            if ((1 << i) & mask)
                portal_distance[i] = min(portal_distance[i], distances[portals[i].first][portals[i].second]);
    }

    if (answer == kInfinite)
        answer = -1;
    cout << answer << "\n";
}
