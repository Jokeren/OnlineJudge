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
static const int N = 110;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;
static const int MOD = 1000000000 + 7;

int arr[N][N];
int dp[N][N];

void solve(int n)
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (j == 1) {
				dp[i][j] = arr[i][j] + dp[i - 1][j];
			}
			else if (j == i) {
				dp[i][j] = arr[i][j] + dp[i - 1][j - 1];
			} else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - 1]) + arr[i][j];
			}
		}
	}

	int max = MIN;
	for (int i = 1; i <= n; i++) {
		max = std::max(dp[n][i], max);
	}

	printf("%d\n", max);

	memset(dp, 0, sizeof(dp));
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n;

	while (scanf("%d", &n) != EOF) {
		solve(n);
	}

	return 0;
}