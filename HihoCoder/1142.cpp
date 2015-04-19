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
static const int N = 1010;
static const int M = 1000010;
static const int LEN = 210;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-8;
static const int BASE = 100007;
static const int CH = 27;

double inline cal_y(double x, double a, double b ,double c)
{
    return a * x * x + b * x + c;
}

void solve(double a, double b, double c, double x, double y)
{
    double l = -200.0f, r = 200.0f;

    while (r - l > EPS) {
        double t0 = l + (r - l) * 1.0f / 3.0f;
        double t1 = l + (r - l) * 2.0f / 3.0f;
        double v0 = cal_y(t0, a, b, c);
        double v1 = cal_y(t1, a, b, c);
        double d0 = (x - t0) * (x - t0) + (y - v0) * (y - v0);
        double d1 = (x - t1) * (x - t1) + (y - v1) * (y - v1);
		
		//极值在左
        if (d1 - d0 > EPS) {
            r = t1;
        } else {//极值在右
            l = t0;
        }
    }

    double v = cal_y(l, a, b, c);
    double d = sqrt((x - l) * (x - l) + (y - v) * (y - v));

    printf("%.3f\n", d + EPS);
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    double a, b, c, x, y;
    while (scanf("%lf %lf %lf %lf %lf", &a, &b, &c, &x, &y) != EOF) {
        if (fabs(cal_y(x, a, b, c) - y) < EPS) {
            printf("0.000\n");
        } else {
            solve(a, b, c, x, y);
        }
    }
    return 0;
}
