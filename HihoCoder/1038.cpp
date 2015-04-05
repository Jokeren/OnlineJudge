#define _USE_MATH_DEFINES

#ifdef ONLINE_JUDGE
#define FINPUT(file) 0
#define FOUTPUT(file) 0
#else
#define FINPUT(file) freopen(file,"r",stdin)
#define FOUTPUT(file) freopen(file,"w",stdout)
#endif

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <set>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

typedef long long ll;
static const int M = 100010;
static const int N = 510;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

int weight[N];
int value[N];
int dp[M];

void solve(int n, int m)
{
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &weight[i], &value[i]);
	}

	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < n; i++) {
		for (int j = m; j >= weight[i]; j--) {
			dp[j] = std::max(dp[j - weight[i]] + value[i], dp[j]);
		}
	}

	printf("%d\n", dp[m]);
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		solve(n, m);
	}
	return 0;
}