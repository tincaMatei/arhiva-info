/*
 autor Diac Paul
 solutile problema arhitect
 memorie: O(N)
 timp: O(N), functioneaza doar pentru cazul in care pantele sunt de 0-45-90-135
*/
#include <stdio.h>
#define NMax 100005

using namespace std;

typedef struct point {
	int x, y;
} point;

int N;
point p[NMax], p0;
int aliniate; // cate segmente sunt aliniate din start

int main() {
	freopen("arhitect.in", "r", stdin);
	freopen("arhitect.out", "w", stdout);
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		point c[2];
		scanf("%d %d %d %d", &c[0].x, &c[0].y, &c[1].x, &c[1].y);
		// conditia din enunt pentru segmente paralele cu Ox sau Oy
		if (c[0].x == c[1].x || c[0].y == c[1].y) {
			aliniate++;
		}
	}
	
	if (aliniate > N - aliniate) {
		printf("%d\n", aliniate);
	} else {
		printf("%d\n", N - aliniate);
	}
	return 0;
}
