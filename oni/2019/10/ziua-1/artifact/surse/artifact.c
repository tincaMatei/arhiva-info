#include <stdio.h>
#include <string.h>

void swap(long long *x, long long *y) {
    long long t = *x; *x = *y; *y = t;
}

long long count(long long k, long long n, long long sum, long long *digits, long long *zero, long long *x) {
    if (k == n) return (sum == 0);
    long long i, cnt = 0;
    for (i = k; i < 10; i++) {
        swap(digits + k, digits + i);
        if (digits[k] || zero[k]) {
            cnt += count(k + 1, n, sum + digits[k]*x[k], digits, zero, x);
        }
        swap(digits + k, digits + i);
    }
    return cnt;
}

int main() {
    FILE    *f = fopen("artifact.in",  "r");
    FILE    *g = fopen("artifact.out", "w");
    char    word[16];
    long long     pos[26], zero[10], x[10];
    long long     digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long     n, m, i, j, ten, nLetters = 0;

    for (i = 0; i < 26; i++) pos[i]  = -1;
    for (i = 0; i < 10; i++) zero[i] = +1, x[i] = 0;
    
    fscanf(f, "%lld%lld", &n, &m);
    for (i = 1; i <= n; i++) {
        fscanf(f, "%s", word);
        for (j = strlen(word) - 1, ten = 1; j >= 0; j--, ten *= 10) {
            if (pos[word[j] - 'A'] == -1) pos[word[j] - 'A'] = nLetters++;
            x[pos[word[j] - 'A']] += ten;
        }
        if (strlen(word) > 1) zero[pos[word[0] - 'A']] = 0;
    }
	for (i = 1; i <= m; i++) {
        fscanf(f, "%s", word);
        for (j = strlen(word) - 1, ten = 1; j >= 0; j--, ten *= 10) {
            if (pos[word[j] - 'A'] == -1) pos[word[j] - 'A'] = nLetters++;
            x[pos[word[j] - 'A']] -= ten;
        }
        if (strlen(word) > 1) zero[pos[word[0] - 'A']] = 0;
    }
    fprintf(g, "%lld", count(0, nLetters, 0, digits, zero, x));

    fclose(f);
    fclose(g);

    return 0;
}
