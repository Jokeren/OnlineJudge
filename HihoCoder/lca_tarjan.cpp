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
static const int M = 100010;
static const int LEN = 100;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10007;
static const int CH = 27;

struct edge {
    int to;
    int id;
}edges[2 * M];

std::map<std::string, int> mp;
std::map<int, std::string> dict;
std::vector<int> g[N];
std::vector<int> search[N];
int color[N];
int parent[N];
int res[N];

void init() {
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }
}

int find_parent(int x)
{
    if (x != parent[x]) {
        return parent[x] = find_parent(parent[x]);
    } else {
        return parent[x];
    }
}

void dfs(int root)
{
    color[root] = 1;//gray

    for (int j = 0; j < search[root].size(); j++) {
        int next = edges[search[root][j]].to;
        int id = edges[search[root][j]].id;
        //printf("root %s search %s\n", dict[root].c_str(), dict[next].c_str());
        if (color[next] == 1) {
            res[id] = next;
        } else if (color[next] == 2) {
            res[id] = find_parent(next);
        } else {
            //do nothing
        }
    }

    for (int i = 0; i < g[root].size(); i++) {
        int next = g[root][i];
        //printf("next %s\n", dict[next].c_str());
        dfs(next);
        parent[next] = root;
    }

    color[root] = 2;
}

void solve(int m)
{
    dfs(1);

    for (int i = 0; i < m; i++) {
        printf("%s\n", dict[res[i]].c_str());
    }
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    init();
    int n, m;

    char father[100], son[100];
    while (scanf("%d", &n) != EOF) {
        int ncount = 1;

        for (int i = 1; i <= n; i++){
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

        scanf("%d", &m);
        int nedge = 0;
        for (int i = 0; i < m; i++) {
            scanf("%s %s", father, son);
            edges[nedge].id = i;
            edges[nedge].to = mp[son];
            //printf("mp[son] %d\n", mp[son]);
            search[mp[father]].push_back(nedge++);
            edges[nedge].id = i;
            edges[nedge].to = mp[father];
            //printf("mp[father] %d\n", mp[father]);
            search[mp[son]].push_back(nedge++);
        }

        solve(m);
    }

    return 0;
}
