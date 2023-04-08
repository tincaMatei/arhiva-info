#include <cassert>
#include <cstdio>

using namespace std;

const int max_n = 1e6;
const int max_m = 1e6;
const int max_time = 1e9;

struct cell {
    int count, type;

    cell(int c, int t) {
        count = c;
        type = t;
    }

    cell() { count = type = 0; }
};

int n, m;
cell cells[max_n + 5];
int prev[max_n + 5];
int next[max_n + 5];

// this compresses one less step in order to ensure
// that the case where a sand moves to the bottom
// of a section remains correct
int find(int pos, int *v) {
    if (cells[v[pos]].type != 0) {
        return v[pos];
    }

    int dst = v[pos];
    while (cells[dst].type == 0) {
        dst = v[dst];
    }

    while (v[pos] != dst) {
        int tmp = v[pos];
        v[pos] = dst;
        pos = tmp;
    }

    return dst;
}

int main() {
    freopen("nisip.in", "r", stdin);
    freopen("nisip.out", "w", stdout);

    scanf("%d%d", &n, &m);

    assert(1 <= n && n <= max_n);
    assert(1 <= m && m <= max_m);

    // prev/next bounds
    prev[1] = 0;
    next[n] = n + 1;

    cells[0] = cells[n + 1] = cell(1, 2);

    // read and compress
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cells[i].type);
        assert(cells[i].type >= 0 && cells[i].type <= 2);

        cells[i].count = 1;

        if (i > 1 && cells[i - 1].type == 1 && cells[i].type == 1) {
            cells[i].count += cells[i - 1].count;
            cells[i - 1] = cell(1, 0);
        }
    }

    // compute prev
    for (int i = 1; i <= n + 1; i++) {
        if (cells[i - 1].type == 1 || cells[i - 1].type == 2) {
            prev[i] = i - 1;
        } else {
            prev[i] = prev[i - 1];
        }
    }

    // compute next
    for (int i = n; i >= 0; i--) {
        if (cells[i + 1].type == 1 || cells[i + 1].type == 2) {
            next[i] = i + 1;
        } else {
            next[i] = next[i + 1];
        }
    }

    // solve queries
    int last_del = -1, last_del_y, prev_x = 0;
    for (int i = 1; i <= m; i++) {
        int task, x, y;
        scanf("%d%d%d", &task, &x, &y);
        assert(task == 1 || task == 2);
        assert(1 <= y && y <= n);
        assert(1 <= x && x <= max_time);
        assert(prev_x <= x);
        prev_x = x;

        if (task == 1) {
            // We need to update the structure of the sand from the previous
            // query
            if (last_del != -1) {
                int sand_pos = find(last_del_y, prev);
                int next_pos = find(last_del_y, next);

                // if sand was above this cell it means movement was made
                if (cells[sand_pos].type == 1) {

                    int prev_stone = prev[sand_pos];

                    if (cells[next_pos].type == 1) {
                        // there's already sand at the bottom of the section

                        // we simply 'delete' a cell and add its contents to the
                        // bottom
                        cells[next_pos].count += cells[sand_pos].count;
                        cells[sand_pos] = cell(1, 0);

                        // we update its neighbours accordingly
                        next[prev_stone] = next[sand_pos];
                        prev[next_pos] = prev[sand_pos];
                    } else {
                        // there's no sand at the bottom so we 'move' it to the
                        // bottom
                        cells[next_pos - 1] = cells[sand_pos];
                        cells[sand_pos] = cell(1, 0);

                        // we update the neighbours accordingly

                        // make sure the previous air cell points to the right
                        // cell
                        next[next_pos - 2] = next_pos - 1;
                        // make sure the previous stone points to the right cell
                        next[prev_stone] = next_pos - 1;
                        // make sure the next stone points to the right cell
                        prev[next_pos] = next_pos - 1;
                        // make sure the new sand points to the prev stone
                        prev[next_pos - 1] = prev_stone;
                    }
                }
            }

            // We phisically delete the current stone cell
            assert(cells[y].type == 2);

            last_del = x;
            last_del_y = y;
            cells[y] = cell(1, 0);
            next[prev[y]] = next[y];
            prev[next[y]] = prev[y];
        } else {
            // we queried a stone, which is a static object
            if (cells[y].type == 2) {
                printf("2\n");
                continue;
            }

            // find prev/next solid object
            int prev_y = find(y, prev);
            int next_y = find(y, next);

            // the next two while loops will always do at most 2 iterations
            // since we can have at most 2 sand piles in each section

            // find prev stone
            while (cells[prev_y].type == 1) {
                prev_y = prev[prev_y];
            }

            // find next stone
            while (cells[next_y].type == 1) {
                next_y = next[next_y];
            }

            // there's no sand in this section
            if (next[prev_y] == next_y) {
                printf("0\n");
                continue;
            }

            int bottom = next_y;
            // there's sand at the bottom of this section
            if (prev[next_y] == next_y - 1) {
                bottom -= cells[next_y - 1].count;
                // if cell is under the bottom of the sand
                if (y >= bottom) {
                    printf("1\n");
                    continue;
                }
            }

            int sand_pos = next[prev_y];
            int sand_len = cells[sand_pos].count;

            // the sand is under the cell
            if (y < sand_pos - sand_len + 1) {
                printf("0\n");
                continue;
            }

            // the cell is inside the unsettled sand pile
            if (x + y <= sand_pos + last_del + 1) {
                printf("1\n");
                continue;
            }

            // the cell is inside the settled sand pile
            if (x + y >= 2 * bottom + last_del - (sand_pos + 1) &&
                bottom - y <= sand_len) {
                printf("1\n");
                continue;
            }

            // the sand didn't get to the cell yet
            if (y - x > sand_pos - last_del - 1) {
                printf("0\n");
                continue;
            }

            // the sand already went past the cell
            if (y - x < sand_pos - last_del - 1 - 2 * (sand_len - 1)) {
                printf("0\n");
                continue;
            }

            // the sand is currently flowing through the cell
            if ((y - x + sand_pos - last_del - 1) % 2 == 0) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }

    return 0;
}
