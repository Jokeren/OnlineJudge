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
static const int N = 1000010;
static const int M = 20;
static const int LEN = 100;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int BASE = 10007;
static const int CH = 27;

int pre_calc[2 * N][M];

void build(int n)
{
    int t = (int)log2(n) + 1;
    for (int j = 1; j < t; j++) {
        for (int i = 0; i < n; i++) {
            pre_calc[i][j] = std::min(
            pre_calc[i][j - 1],
            pre_calc[i + (1<<(j - 1))][j - 1]);
        }
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 1; j < t && (i + 1<<(j - 1)) < n; j++) {
//            printf("i %d j %d: %d\n", i, j, pre_calc[i][j]);
//        }
//    }
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int n, m;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &pre_calc[i][0]);
        }

        build(n);

        scanf("%d", &m);
        int l, r;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &l, &r);
            l--;
            r--;
            int mid = log2(r - l + 1);
            printf("%d\n", std::min(pre_calc[l][mid],
                                    pre_calc[r - (1<<mid) + 1][mid]));
        }
    }

    return 0;
}
