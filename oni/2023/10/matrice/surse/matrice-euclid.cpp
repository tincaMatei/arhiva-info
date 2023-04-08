// stud. Bogdan Vlad-Mihai 
// Universitatea din București
// Soluție cu Extended Euclid cu timp O(T) și memorie O(1)
#include <bits/stdc++.h>

const int MOD = 1e9 + 9;

int N, M, T; 
int x, y, g, a, b;

int extendedEuclid(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x0, y0;
    int d = extendedEuclid(b, a % b, x0, y0);
    x = y0;
    y = x0 - y0 * (a / b);
    return d;
}

void add(int a, int b, int &x, int &y, int k) {
    x += b * k;
    y -= a * k;
}

int countSolutions(int target, int x, int y, int g) {
    add(a, b, x, y, (1 - x) / b);
    if (x < 1) {
        add(a, b, x, y, 1);
    }
    int lowX = x;
    add(a, b, x, y, (T - x) / b);
    if (x > T) {
        add(a, b, x, y, -1);
    }
    if (x > T) {
        return 0;
    }
    int upX = x;
    add(a, b, x, y, -(1 - y) / a);
    if (y < 1) {
        add(a, b, x, y, -1);
    }
    if (y > T) {
        return 0;
    }
    int lowY = x;
    add(a, b, x, y, -(T - y) / a);
    if (y > T) {
        add(a, b, x, y, 1);
    }
    int upY = x;
    if (lowY > upY) {
        std::swap(lowY, upY);
    }
    return std::max(0, (std::min(upX, upY) - std::max(lowX, lowY)) / b + 1);
}

int main() {
    assert(freopen("matrice.in", "r", stdin));
    assert(freopen("matrice.out", "w", stdout));

    std::cin >> N >> M >> T;
    if (N < M) {
        std::swap(N, M);
    }

    int answer = 0;
    if (M > 1) {
        g = extendedEuclid(N - 1, M - 1, x, y);
        a = (N - 1) / g, b = (M - 1) / g;

        int count = 0, totalCount = 0;
        for (int target = 1; target <= T; target++) {
            if (target % g == 0) {
                count += countSolutions(target, (target / g) * x, (target / g) * y, g);
                if (count >= MOD) {
                    count -= MOD;
                }
            }
            totalCount += count;
            if (totalCount >= MOD) {
                totalCount -= MOD;
            }
            if ((T - target) % ((N - 1) * (M - 1)) == 0) {
                answer += totalCount;
                if (answer >= MOD) {
                    answer -= MOD;
                }
            }
        }
    } else if (N > 1) {
        for (int f = 0; f <= T; f++) {
            answer += (T - f) / (N - 1);
            if (answer >= MOD) {
                answer -= MOD;
            }
        }
    } else {
        answer = T + 1;
    }
    
    std::cout << answer << "\n";
    return 0;
}