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
static const int M = 10010;
static const int N = 1010;
static const int CH = 27;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10;
static const int MOD = 1000000007;

int dp[N][1 << 5];
int f[] = { 3, 6, 12, 24, 15, 27, 30 };

void solve(int n, int m)
{
	memset(dp, 0, sizeof(dp));

	dp[0][(1 << m) - 1] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < (1 << m); j++) {
			int cur_state = ((1 << m) - 1) ^ j;
			(dp[i][cur_state] += dp[i - 1][j]) %= MOD;
			for (int k = 0; k < 7; k++) {
				if (f[k] >= (1 << m) || (f[k] & cur_state))
					continue;
				(dp[i][f[k] | cur_state] += dp[i - 1][j]) %= MOD;
			}
		}
	}


	//for (int i = 1; i <= n; i++) {
	//	for (int j = 0; j < (1 << m); j++) {
	//		printf("i %d j %d dp %d\n", i, j, dp[i][j]);
	//	}
	//}

	printf("%d\n", dp[n][(1 << m) - 1]);
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n, m;

	while (scanf("%d %d ", &n, &m) != EOF) {
		if ((n * m) & 1)//notice
			printf("0\n");
		else 
			solve(n, m);
	}
	
	return 0;
}