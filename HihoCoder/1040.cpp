/*
 * 利用矩形的性质，首先找id为0的线的两条垂线。
 * 如果可以找到，并且第4条线和两条垂线也垂直（或者说和id为0的线平行），就是矩形。
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

std::string str;

struct line_t {
    int x1, y1;
    int x2, y2;
    double k;
}line[4];

bool inline tang(int x1, int x2, int x3, int x4, int y1, int y2,
                 int y3, int y4)
{
    if ( (x1 - x2) == 0) {
        return (y3 - y4 == 0);
    } else if ( (x3 - x4) == 0) {
        return (y1 - y2 == 0);
    } else {
        return ((y1 - y2) * (y3 - y4) / ((x1 - x2) * (x3 - x4)) == -1);
    }
}

void solve()
{
    int tan1 = -1, tan2 = -1;
    for (int i = 1; i < 4; ++i) {
        if (tan1 != -1 && tan2 != -1)
            break;
        if ((line[i].x1 == line[0].x1 &&
        line[i].y1 == line[0].y1) || (line[i].x2 == line[0].x1 &&
        line[i].y2 == line[0].y1) || (line[i].x1 == line[0].x2 &&
        line[i].y1 == line[0].y2) || (line[i].x2 == line[0].x2 &&
        line[i].y2 == line[0].y2)) {
            if (tang(line[0].x1, line[0].x2, line[i].x1, line[i].x2,
                     line[0].y1, line[0].y2, line[i].y1, line[i].y2)) {
                if (tan1 == -1) {
                    tan1 = i;
                } else {
                    tan2 = i;
                }
            }
        }
    }
    if (tan1 == -1 || tan2 == -1) {
        printf("NO\n");
        return;
    }

    int t = -1;
    for (int i = 1; i < 4; ++i) {
        t = i;
        if (t != tan1 && t != tan2) {
            break;
        }
    }

    tan1 = -1, tan2 = -1;
    for (int i = 1; i < 4; ++i) {
        if (tan1 != -1 && tan2 != -1)
            break;
        if ((line[i].x1 == line[t].x1 &&
        line[i].y1 == line[t].y1) || (line[i].x2 == line[t].x1 &&
        line[i].y2 == line[t].y1) || (line[i].x1 == line[t].x2 &&
        line[i].y1 == line[t].y2) || (line[i].x2 == line[t].x2 &&
        line[i].y2 == line[t].y2)) {
            if (tang(line[t].x1, line[t].x2, line[i].x1, line[i].x2,
                     line[t].y1, line[t].y2, line[i].y1, line[i].y2)) {
                if (tan1 == -1) {
                    tan1 = i;
                } else {
                    tan2 = i;
                }
            }
        }
    }
    if (tan1 == -1 || tan2 == -1) {
        printf("NO\n");
        return;
    } else {
        printf("YES\n");
    }
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 4; ++j) {
                scanf("%d %d %d %d", &line[j].x1, &line[j].y1,
                      &line[j].x2, &line[j].y2);
            }

            solve();
        }
    }

    return 0;
}

