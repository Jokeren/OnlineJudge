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
static const int N = 1000100;
static const int M = 19;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 1000000007;
static const int CH = 27;


struct Trie {
    //N代表节点个数，通常为字符串长度*字符串个数
    //数据量太大时要用new
    int ch[N][CH];
    int value[N][CH];
    int sz;
    Trie():sz(1) {
        memset(ch[0], 0, sizeof(ch[0]));
        memset(value[0], 0, sizeof(value[0]));
    }

    void init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(value[0], 0, sizeof(value[0]));
    }

    void insert(char *s, int v) {
        int u = 0, n = strlen(s);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a' + 1;
            if (!ch[u][c]) {
                //大量节省时间
                memset(ch[sz], 0, sizeof(ch[sz]));
                memset(value[sz], 0, sizeof(value[sz]));
                ch[u][c] = sz++;
            }
            ++value[u][c];
            u = ch[u][c];
        }
    }

    int search(char *s) {
        int u = 0, n = strlen(s);
        int ret;
        int c;

        for (int i = 0; i < n; i++) {
            c = s[i] - 'a' + 1;
            if (ch[u][c] != 0) {
                ret = value[u][c];
                u = ch[u][c];
            } else {
                return 0;
            }
        }

        return ret;
    }
};

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int n, m;
    //数据量太大时要用new
    struct Trie *trie = new Trie();
    while (scanf("%d", &n) != EOF) {
        char str[12];
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            trie->insert(str, i);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%s", str);
            printf("%d\n", trie->search(str));
        }

        trie->init();
    }

    return 0;
}
