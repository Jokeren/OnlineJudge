/*
 * 矩阵快速幂
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
#include <limits>

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
static const ll BASE = 19999997;
static const int CH = 27;

typedef std::vector<ll> matrix[2];

void inline mul(matrix& a, matrix& b)
{
    ll ret[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ll ans = 0;
            for (int k = 0; k < 2; ++k) {
                ans += a[i][k] * b[k][j];
            }
            ret[i][j] = ans;
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            a[i][j] = ret[i][j];
        }
    }
}

void mod(matrix& t)
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            t[i][j] %= BASE;
        }
    }
}

void binary_power(matrix& a, ll b)
{
    matrix tmp;
    tmp[0].push_back(1LL);
    tmp[0].push_back(0LL);
    tmp[1].push_back(0LL);
    tmp[1].push_back(1LL);

    while(b!=0LL){
        if(b%2LL == 1LL){
            mul(tmp, a);
            mod(tmp);
        }
        b /= 2LL;
        mul(a, a);
        mod(a);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            a[i][j] = tmp[i][j];
        }
    }
}
int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    ll t;
    while (scanf("%lld", &t) != EOF) {
        if (t == 2LL) {
            printf("2\n");
        } else if (t == 1LL) {
            printf("1\n");
        } else {
            matrix st;
            st[0].push_back(1LL);
            st[0].push_back(2LL);
            matrix m;
            m[0].push_back(0LL);
            m[0].push_back(1LL);
            m[1].push_back(1LL);
            m[1].push_back(1LL);
            ll ret[1][2];
            memset(ret, 0, sizeof(ret));
            binary_power(m, t - 2LL);

            for (int i = 0; i < 1; ++i) {
                for (int j = 0; j < 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        ret[i][j] += st[i][k] * m[k][j];
                    }
                    ret[i][j]%=BASE;
                }
            }

            printf("%lld\n", ret[0][1]);
        }
    }

    return 0;
}
