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
static const int M = 10;
static const int N = 1010;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

int train[N];
int dp[N][2 << 10 + 1];
int ncount[N];

int inline count_one(int num)
{
	int cntx = 0;
	while (num) {
		if (num & 1) cntx++;
		num >>= 1;
	}
	return cntx;
}

void solve(int n, int m, int q)
{
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < n; i++) {
		scanf("%d", &train[i]);
	}

	int limit = 1 << (m - 1);
	for (int i = 0; i < limit; i++) {
		ncount[i] = count_one(i);
	}

	dp[0][0] = 0;
	dp[0][1] = train[0];

	for (int i = 1; i < n; i++) {
		if (i < m - 1) { 
			int max_j = (1 << i);
			for (int j = 0; j < max_j; j++) {
				int nchoose = ncount[j];
				if (nchoose < q) {
					dp[i][j + max_j] = dp[i - 1][j] + train[i];
				}
				dp[i][j] = dp[i - 1][j];
				//printf("j:%d dp[i - 1][j]:%d\n", j, dp[i - 1][j]);
				//printf("1 i:%d, j:%d, j + max_j:%d, value:%d, value:%d\n", i, j, j + max_j, dp[i][j] = dp[i - 1][j], dp[i][j + max_j]);
			}
		}
		else {
			int max_j = limit;
			for (int j = 0; j < max_j; j++) {
				int nchoose = ncount[j];
				if (nchoose < q) {
					dp[i][(j >> 1) + (max_j >> 1)] = std::max(dp[i - 1][j] + train[i], dp[i][(j >> 1) + (max_j >> 1)]);
				}
				dp[i][(j >> 1)] = std::max(dp[i][j >> 1], dp[i - 1][j]);
				//printf("2 i:%d, j>>1:%d, max_j>>1+j>>1:%d, value:%d, value:%d\n", i, j >> 1, (j >> 1) + (max_j >> 1), dp[i][j >> 1], dp[i][(j >> 1) + (max_j >> 1)]);
			}
		}
	}

	int ans = MIN;
	for (int i = 0; i < limit; i++) {
		ans = std::max(ans, dp[n - 1][i]);
	}
	printf("%d\n", ans);
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n, m, q;
	while (scanf("%d %d %d", &n, &m, &q) != EOF) {
		solve(n, m, q);
	}
	return 0;
}