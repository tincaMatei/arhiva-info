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

int countFixedSolutions(int max_elem) {
	int answer = 0;
	if(!max_elem)
		return 0;
	while(max_elem)	{
		digits.push_back(max_elem % 10);
		max_elem /= 10;
	}
	for(int i = 1; i < (int)digits.size(); i++) {
		answer += pow(9, i);
	}
	
	for(int i = digits.size() - 1; i >= 0; i--) {
		if(!digits[i])
			return answer;
		answer += pow(9, i) * (digits[i] - 1);
	}
	
	return answer + 1;
}

int noZeroVerdict(int value) {
	if(!value)
		return 1;
	return ((value % 10 != 0) & noZeroVerdict(value / 10));
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
//	printf("last = %d si answer = %d\n", last, answer);
	
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

