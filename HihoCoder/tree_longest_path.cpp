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
static const int M = 100;
static const int N = 100010;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;
static const int MOD = 1000000000 + 7;

std::vector<std::vector<int> > g(N);
bool visit[N];
int max = 0;
int root;

std::pair<int, int> traverse(int start)
{
	std::pair<int, int> tmp;
	visit[start] = true;

	if (g[start].size() == 1 && visit[g[start][0]]) {
		tmp.first = 0;
		tmp.second = 0;
		return tmp;
	}
	else {
		std::pair<int, int> ret;
		ret.first = 0;
		ret.second = 0;
		for (int i = 0; i < g[start].size(); i++) {
			if (visit[g[start][i]])
				continue;

			tmp = traverse(g[start][i]);

			/* only the first value is used to update the first and second value
			 */
			if (tmp.first > ret.first) {
				ret.second = ret.first;
				ret.first = tmp.first;
			}
			else if (tmp.first > ret.second) {
				ret.second = tmp.first;
			}
			//printf("2:start %d first %d second %d\n", start, ret.first, ret.second);
		}

		/* if there's no left or right tree
		*/
		ret.first++;
		if ((g[start].size() == 2 && start != root) ||
			(start == root && g[start].size() == 1))
			ret.second = 0;
		else
			ret.second++;

		max = std::max(max, ret.first + ret.second);
		//printf("1:start %d first %d second %d\n", start, ret.first, ret.second);
		return ret;
	}
}
void solve(int n)
{
	memset(visit, false, sizeof(visit));
	int v, u;

	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &v, &u);
		g[v].push_back(u);
		g[u].push_back(v);
	}

	std::pair<int, int> p;
	root = 1;
	p = traverse(1);

	printf("%d\n", max);

	for (int i = 0; i <= n; i++) {
		g[i].clear();
	}
	max = 0;
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n;
	scanf("%d", &n);
	solve(n);

	return 0;
}