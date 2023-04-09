/*
 autor Diac Paul
 solutile problema arhitect
 memorie: O(N)
 timp: O(N^2)
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#define NMax 100005

using namespace std;

typedef struct point {
	int x, y;
} point;

int N;
point p[NMax], p0;

// distanta la patrat
long long distSq(point A, point B) { return ((long long)A.x-B.x)*(A.x-B.x)+((long long)A.y-B.y)*(A.y-B.y); }
// aria cu semn a triunghiului (0,0)-A-B
long long area00(point A, point B) { return (long long)A.x*B.y-(long long)A.y*B.x; }
// teorema lui Pitagora pentru a verifica unghiul drept BAC
int isA90(point A, point B, point C) { return (distSq(B,C) == (distSq(A,B) + distSq(A,C))); }

int main() {
	freopen("arhitect.in", "r", stdin);
	freopen("arhitect.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		point c[2];
		scanf("%d %d %d %d", &c[0].x, &c[0].y, &c[1].x, &c[1].y);
		c[1].x -= c[0].x; c[1].y -= c[0].y;
		p[i] = c[1];
	}
	int max = 0;
	for (int i = 0; i < N; i++) {
		int aliniat = 1;
		for (int j = i + 1; j < N; j++) {
			if (isA90(p0, p[i], p[j]) || area00(p[i], p[j]) == 0) {
				aliniat++;
			}
		}
		if (max < aliniat) {
			max = aliniat; }
	}
	printf("%d\n", max);
	return 0;
}
