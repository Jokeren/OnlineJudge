/*
 * ��λdp
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
static const int N = 30;
static const int M = 30010;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 1000000007;
static const int CH = 258;

int l_num[N];
int r_num[N];
int l_len, r_len;
ll pow_ten[N];
ll f[N][N][500];
ll dp[N][N][500];

void init()
{
    pow_ten[0] = 1;
    for (int i = 1; i < 20; ++i) {
        pow_ten[i] = pow_ten[i - 1] * 10LL;
    }
}

void calc()
{
    f[0][0][220] = 0LL;
    dp[0][0][220] = 1LL;

    for (int i = 1; i < 20; ++i) {
        for (int j = 0; j <= 9; ++j) {
            for (int k = 0; k <= 9; ++k) {
                for (int t = -200; t <= 200; ++t) {
					//dp[i][j][t + 220 + j]�������ǰ�ǵ�iλ��ǰһλΪj����Ϊt+220+j�����ֵĸ���
					//��Ϊ��λ����Ϊt+j������ǰһλ����һ��Ϊ-t
                    dp[i][j][t + 220 + j] +=
                    dp[i - 1][k][-t + 220];
                    dp[i][j][t + 220 + j] %= BASE;

					//f[i][j][t + 220 + j]�������ǰ�ǵ�iλ��ǰһλΪj����Ϊt+220+j�����ֵĺͣ���Ȼ��Ҫ
					//����ǰһλ�������ֵĺͲ��Ҽ��ϵ�ǰ����*��ǰ���ֵĸ�����
                    f[i][j][t + 220 + j] += f[i - 1][k][-t + 220] % BASE;
                    f[i][j][t + 220 + j] +=
                    (((ll)j * pow_ten[i - 1]) % BASE * dp[i - 1][k][-t + 220]) % BASE;
                    f[i][j][t + 220 + j] %= BASE;
                }
            }
        }
    }
}

void solve(ll l, ll r, int k)
{
    l_len = 1;
    while (l > 0) {
        l_num[l_len++] = l % 10LL;
        l /= 10LL;
    }
    l_num[l_len--] = 0;

    r_len = 1;
    while (r > 0) {
        r_num[r_len++] = r % 10LL;
        r /= 10LL;
    }
    r_num[r_len--] = 0;

    memset(f, 0, sizeof(f));
    memset(dp, 0, sizeof(dp));
    calc();

    ll ans_l = 0LL;
    int tmp = 0;
    ll tmp_sum = 0LL;
    int flag = 1;
	//����ͳ������С����l_num�����Һ�Ϊk���������ֺͣ���һλһ��Ϊ1
    for (int i = l_len; i >= 1; --i) {
        for (int j = i == l_len ? 1 : 0; j < l_num[i]; ++j) {
			//�������֣���һ�����ּ��ϵ��Ǵ�iλ��0λ������
            ans_l += f[i][j][flag * (k - tmp) + 220];
            ans_l %= BASE;
			//�ڶ������ּ��ϵ��Ǵ�l_len����iλ������
            ans_l += (pow_ten[i] % BASE) * ((tmp_sum % BASE * dp[i][j][flag * (k - tmp) + 220]) % BASE);
            ans_l %= BASE;
        }
        tmp += flag * l_num[i];
        tmp_sum = tmp_sum * 10LL + l_num[i];
        flag = -flag;
    }
	//���ͳ�Ƶ��Ǵ�l_len-1λ������0λ��ǰ������Ϊ0�ĺ�
    for (int i = 1; i < l_len; ++i) {
        for (int j = 1; j <= 9; ++j) {
            ans_l += f[i][j][k + 220];
            ans_l %= BASE;
        }
    }

    ll ans_r = 0LL;
    tmp = 0;
    tmp_sum = 0LL;
    flag = 1;
    for (int i = r_len; i >= 1; --i) {
        for (int j = i == r_len ? 1 : 0; j < r_num[i]; ++j) {
            ans_r += f[i][j][flag * (k - tmp) + 220];
            ans_r %= BASE;
            ans_r += (pow_ten[i] % BASE) * ((tmp_sum % BASE * dp[i][j][flag * (k - tmp) + 220]) % BASE);
            ans_r %= BASE;
        }
        tmp += flag * r_num[i];
        tmp_sum = tmp_sum * 10LL + r_num[i];
        flag = -flag;
    }
    for (int i = 1; i < r_len; ++i) {
        for (int j = 1; j <= 9; ++j) {
            ans_r += f[i][j][k + 220];
            ans_r %= BASE;
        }
    }

    ll t = ans_r - ans_l;
    while (t < 0) {
        t += BASE;
    }
    
    printf("%lld\n", t);
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int k;
    ll l, r;
    init();
    while (scanf("%lld %lld %d", &l, &r, &k) != EOF) {
        solve(l + 1, r + 1, k);
    }

    return 0;
}

