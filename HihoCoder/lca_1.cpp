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
static const int N = 110;
static const int M = 30;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10;

std::map<std::string, int> mp;
std::vector<std::vector<int> > rg(N);
char out[N][M], name_a[M], name_b[M];
int traverse[N];

void solve(int idx_a, int idx_b)
{
	int idx = idx_a;

	while (true) {
		traverse[idx] = 1;
		if (rg[idx].size() == 0) {
			break;
		}
		idx = rg[idx][0];
	}

	idx = idx_b;

	while (true) {
		if (traverse[idx]) {
			printf("%s\n", out[idx]);
			break;
		}
		else if (rg[idx].size() == 0) {
			printf("-1\n");
			break;
		}
		idx = rg[idx][0];
	}

	memset(traverse, 0, sizeof(traverse));
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n, m;
	while (scanf("%d ", &n) != EOF) {
		int ncount = 1;
		char father[M], son[M];

		for (int i = 0; i < n; i++) {
			scanf("%s %s", father, son);
			if (mp[father] == 0) {
				mp[father] = ncount;
				strcpy(out[ncount], father);
				ncount++;
			}
			if (mp[son] == 0) {
				mp[son] = ncount;
				strcpy(out[ncount], son);
				ncount++;
			}

			rg[mp[son]].push_back(mp[father]);
		}

		scanf("%d ", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s %s", name_a, name_b);
			if (strcmp(name_a, name_b) == 0) {
				printf("%s\n", name_a);
			}
			else {
				if (mp[name_a] == 0 || mp[name_b] == 0) {
					printf("-1\n");
				}
				else
					solve(mp[name_a], mp[name_b]);
			}
		}

		for (int i = 0; i < N; i++) {
			rg[i].clear();
		}
	}

	return 0;
}