/*
 * ö�����о��ε����������ö�����Ͻǣ�Ȼ��ö�ٱ߳���
 * �����ж�������ĸ��˵��Ƿ���ö�ٵľ����ڣ������һ���˵�������ֱ�Ӽ�ȥ����
 * ����������˵㣬�򲻳�����������ĸ��˵��ڣ���������
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
				//����ط���ʹv>=m��ҲҪ����ö�٣�������ܵ����û�п�����ȫ
				//..............
				//..............
				//************..
				//************..
				//..............
				//����˵���������ԭ��v = max����h = 3������ʵ����h = 1��ʱ���������
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
