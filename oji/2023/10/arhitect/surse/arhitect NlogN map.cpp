/*
 autor Apostol Ilie-Daniel
 punctaj maxim
 segmentele sunt simplificate si retinute intr-un map <>
*/
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <map>

int main() {
    freopen("arhitect.in", "r", stdin);
    freopen("arhitect.out", "w", stdout);
    int N;
    std:: cin >> N;
    std::map <std::pair <int, int>, int> slopes;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        int x = x1 - x2;
        int y = y1 - y2;
        if (x == 0 || y == 0) {
            slopes[{0, 0}]++;
        }
        else {
            int g = std::__gcd(abs(x), abs(y));
            x /= g, y /= g;
            if (y < 0)
                x = -x, y = -y;
            if (x < 0)
                std::swap(x, y), y = -y;
            slopes[{x, y}]++;
        }
    }
    int answer = 0;
    for (auto &it : slopes)
        answer = std::max(answer, it.second);
    std::cout << answer << "\n";
    return 0;
}
