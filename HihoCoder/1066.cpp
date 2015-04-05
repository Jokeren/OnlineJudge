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
static const int N = 100010;
static const int M = 70;
static const int LEN = 100;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10007;
static const int CH = 27;

int parent[2 * N];
std::map<std::string, int> mp;
int ncount;

void init(int n)
{
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	ncount = 1;
}

int find_parent(int x)
{
	if (parent[x] != x) {
		return parent[x] = find_parent(parent[x]);
	}
	else {
		return parent[x];
	}
}

void union_parent(int t1, int t2)
{
	int p1 = find_parent(t1);
	int p2 = find_parent(t2);

	if (p1 != p2) {
		parent[p1] = p2;
	}
}

void solve()
{
	char name1[LEN], name2[LEN];
	char cmd[3];

	scanf("%s %s %s", cmd, name1, name2);
	if (!mp[name1]) {
		mp[name1] = ncount++;
	}

	if (!mp[name2]) {
		mp[name2] = ncount++;
	}
	if (cmd[0] == '0') {
		union_parent(mp[name1], mp[name2]);
	}
	else {
		int p1 = find_parent(mp[name1]);
		int p2 = find_parent(mp[name2]);

		if (p1 != p2) {
			printf("no\n");
		}
		else {
			printf("yes\n");
		}
	}
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int t;
	while (scanf("%d", &t) != EOF) {
		init(2 * t);
		for (int i = 0; i < t; i++) {
			solve();
		}
		mp.clear();
	}
	return 0;
}
