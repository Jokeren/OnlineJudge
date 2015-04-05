/*
 * 枚举所有矩形的情况，首先枚举左上角，然后枚举边长。
 * 依次判断沼泽的四个端点是否在枚举的矩形内，如果是一个端点的情况，直接减去区域。
 * 如果是两个端点，则不成立。如果在四个端点内，不成立。
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
static const int N = 2010;
static const int M = 19;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 1000000007;
static const int CH = 258;

int ans;
int n, m, L;
int l, r, t, b;

void solve(int sx, int sy, int v, int h)
{
    int rb = std::min(m, sy + v);
    int bb = std::min(n, sx + h);
    int ret = (rb - sy) * (bb - sx);
    if (!(rb <= l || sy >= r || bb <= t || sx >= b)) {
        if (sx > t && bb < b && sy > l && rb < r)
            return;

        int num = 0;
        if (sy < l && sx < t)
            ++num;

        if (sy < l && bb > b)
            ++num;

        if (sx < t && rb > r)
            ++num;

        if (bb > b && rb > r)
            ++num;

        if (num == 0 || num == 2)
            return;

        int uu = std::max(t, sx);
        int ub = std::min(b, bb);
        int ul = std::max(l, sy);
        int ur = std::min(r, rb);
        ret -= (ub - uu) * (ur - ul);
    }

    ans = std::max(ret, ans);
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    while (scanf("%d %d %d", &n, &m, &L) != EOF) {
        scanf("%d %d %d %d", &l, &r, &t, &b);

        ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int h = 1, v = 1;
				//这个地方即使v>=m，也要继续枚举，否则可能的组合没有考虑完全
				//..............
				//..............
				//************..
				//************..
				//..............
				//比如说上述情况，原来v = max，且h = 3，但是实际上h = 1的时候面积更大
                while (true) {
                    h = (L - 2 * v) / 2;
                    if (h <= 0)
                        break;
                    solve(i, j, v, h);
                    ++v;
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
