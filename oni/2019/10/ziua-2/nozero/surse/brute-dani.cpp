#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
using namespace std;

#define NMAX 100005

map<int, bool> apparition;
vector<int> digits;
int n, k, answer;
long long fact[NMAX];

int computeFactorials(int n, int k) {
	fact[0] = 1;
	for(int i = 1; i <= n; i++) {
		fact[i] = fact[i - 1] * i;
		if(fact[i] > k)
			return i - 1;
	}
	return n;
}


int noZeroVerdict(int value) {
	if(!value)
		return 1;
	return ((value % 10 != 0) & noZeroVerdict(value / 10));
}

int countFixedSolutions(int max_elem) {
	for(int i = 1; i <= max_elem; i++) {
		answer += noZeroVerdict(i);
	}
	return answer;
}


int nextActiveValue(int value) {
	value++;
	while(value < n && apparition[value]) {
		value++;
	}
	return value;
}

int main () {

	freopen("nozero.in",  "r", stdin);
	freopen("nozero.out", "w", stdout);
	
	scanf("%d%d", &n, &k);
	k--;

	int last = computeFactorials(n, k);	
	int answer = countFixedSolutions(n - last - 1);
	
	for(int i = n - last; i <= n; i++) {
		int level = n - i;
		int value = nextActiveValue(n - last - 1);
		while(k >= fact[level]) {
			k -= fact[level];
			value = nextActiveValue(value);
		}
		apparition[value] = true;
		answer += (noZeroVerdict(value) & noZeroVerdict(i));
	}
	
	printf("%d\n", answer);


	return 0;
}

