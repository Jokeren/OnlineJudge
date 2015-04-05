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
static const int N = 200;
static const int M = 19;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 10007;
static const int CH = 27;

int arr[N];

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int t;
    while (scanf("%d", &t) != EOF) {
        int n, m;
        for (int i = 0; i < t; ++i) {
            scanf("%d %d", &n, &m);

            for (int i = 1; i <= n; ++i) {
                scanf("%d", &arr[i]);
            }
            arr[0] = 0;
            arr[n + 1] = 100;

            int con_max = 0;
            if (m >= n) {
                con_max = 100;
            } else {
                for (int i = m + 1; i <= n; ++i) {
                    con_max = std::max(con_max,
                                       arr[i] - arr[i - m - 1] - 1);
                }
            }
            printf("%d\n", con_max);
        }
    }

    return 0;
}
