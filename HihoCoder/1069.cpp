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
static const int M = 20;
static const int LEN = 100;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10007;
static const int CH = 27;

std::map<std::string, int> mp;
std::map<int, std::string> dict;
std::vector<int> g[N];
int search[N];
int idx;
int pre_calc[4 * N][M];
int res[4 * N][M];

void dfs(int root, int depth)
{
    res[idx][0] = root;
    pre_calc[idx++][0] = depth;//gray

    for (int i = 0; i < g[root].size(); i++) {
        int next = g[root][i];
        //printf("next %s\n", dict[next].c_str());
        dfs(next, depth + 1);
        res[idx][0] = root;
        pre_calc[idx++][0] = depth;
    }
    search[root] = idx - 1;
}

void build(int n)
{
    int t = (int)log2(n) + 1;
    for (int j = 1; j < t; j++) {
        for (int i = 0; i < n; i++) {
            if (pre_calc[i][j - 1] <
                pre_calc[i + (1<<(j - 1))][j - 1]) {
                pre_calc[i][j] = pre_calc[i][j - 1];
                res[i][j] = res[i][j - 1];
            } else {
                pre_calc[i][j] = pre_calc[i + (1<<(j - 1))][j - 1];
                res[i][j] = res[i + (1<<(j - 1))][j - 1];
            }
        }
    }
}

void solve(int n)
{
    idx = 0;
    dfs(1, 1);
    build(2 * n + 1);
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int n, m;

    char father[100], son[100];
    while (scanf("%d", &n) != EOF) {
        int ncount = 1;

        for (int i = 1; i <= n; i++) {
            scanf("%s %s", father, son);
            if (!mp[father]) {
                dict[ncount] = std::string(father);
                mp[father] = ncount++;
            }

            if (!mp[son]) {
                dict[ncount] = std::string(son);
                mp[son] = ncount++;
            }

            g[mp[father]].push_back(mp[son]);
        }

        solve(n);

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%s %s", father, son);
            int f = search[mp[father]];
            int s = search[mp[son]];
            if (f > s) {
                std::swap(f, s);
            }
            int mid = log2(s - f + 1);
            int ans = 0;
            if (pre_calc[f][mid] <
                pre_calc[s - (1<<mid) + 1][mid]) {
                ans = res[f][mid];
            } else {
                ans = res[s - (1<<mid) + 1][mid];
            }
            printf("%s\n", dict[ans].c_str());
        }
    }

    return 0;
}
