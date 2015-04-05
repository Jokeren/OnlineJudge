/*
 * 预先剪枝搜索。因为自身是树形，所以可以先提前存储某个节点可以到达的所有值。
 */
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
#include <bitset>

typedef long long ll;
typedef long double ld;
static const int N = 120;
static const int M = 30010;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 1000000007;
static const int CH = 258;

std::vector<int> g[N];
int order[N];
bool visit[N][N];
std::bitset<N> reach[N];
bool find;
int idx;

void dfs(int start, int prev)
{
    reach[start][start] = 1;

    for (int i = 0; i < g[start].size(); ++i) {
        int to = g[start][i];
        if (to != prev) {
            dfs(to, start);
            reach[start] |= reach[to];
        }
    }
}

void solve(int start, int m)
{
    if (find) return;

    if (start == order[idx]) {
        //printf("start %d, idx: %d order[idx]: %d\n", start, idx, order[idx]);
        ++idx;
    }

    if (idx == m) {
        //printf("%d\n", idx);
        find = true;
        return;
    }

    while (idx < m) {
        int cur = idx;
        bool flag = false;

        for (int i = 0; i < g[start].size(); ++i) {
            int to = g[start][i];
            if (reach[to][order[idx]] == 1 && !visit[start][to]) {
                //printf("start %d, to: %d\n", start, to);
                visit[start][to] = true;
				//如果从start点本身不可到达，也就是说to节点是父节点，
				//可以用solve(pre)实现
                if (reach[start][order[idx]] == 0) {
                    flag = true;
                }
                solve(to, m);
                if (flag) break;
            }
        }
        if (flag) break;
        if (cur == idx)
            break;
    }
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int t;
    while (scanf("%d", &t) != EOF) {
        for (int i = 0; i < t; ++i) {
            int n;
            scanf("%d", &n);

            int from, to;
            for (int j = 0; j < n - 1; ++j) {
                scanf("%d %d", &from, &to);
                g[from].push_back(to);
                g[to].push_back(from);
            }

            int m;
            scanf("%d", &m);
            for (int j = 0; j < m; ++j) {
                scanf("%d", &order[j]);
            }

            dfs(1, 1);

            find = false;
            idx = 0;
            solve(1, m);

            if (!find) {
                printf("NO\n");
            } else {
                printf("YES\n");
            }

            for (int i = 0; i < N; ++i) {
                g[i].clear();
                reach[i].reset();
            }
            memset(visit, false, sizeof(visit));
        }
    }

    return 0;
}

