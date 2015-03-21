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
static const int M = 1010;
static const int N = 110;
static const int CH = 27;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;
static const int MOD = 1000000000 + 7;

std::vector<std::vector<int> > g(N);
int nodes[N];
int dp[N][N];

void traverse(int m, int idx)
{
	dp[idx][1] = nodes[idx];

	for (int i = 0; i < g[idx].size(); i++) {
		traverse(m, g[idx][i]);
	}

	for (int i = 0; i < g[idx].size(); i++) {
		for (int nchoose = m; nchoose >= 2; nchoose--) {
			for (int m_child = 1; m_child < nchoose; m_child++) {
				dp[idx][nchoose] = std::max(dp[idx][nchoose], dp[idx][nchoose - m_child] + dp[g[idx][i]][m_child]);
			}
		}
	}
}

void solve(int n, int m)
{
	for (int i = 1; i <= n; i++) {
		scanf("%d", &nodes[i]);
	}

	int x, y;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &x, &y);
		if (x < y) {
			g[x].push_back(y);
		}
		else {
			g[y].push_back(x);
		}
	}

	traverse(m, 1);
	printf("%d\n", dp[1][m]);

	memset(dp, 0, sizeof(dp));
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n, m;
	while (scanf("%d %d ", &n, &m) != EOF) {
		solve(n, m);
	}

	return 0;
}