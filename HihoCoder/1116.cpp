/*
 * 查询是O(1)
 * 主要在于每个节点存4个值，一个是当前段内的所有和，
 * 一个是左端点和，一个是右端点和，还有一个连续乘积，这三个用来合并。
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
static const int N = 100100;
static const int M = 19;
static const int LEN = 50;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 10007;
static const int CH = 27;

ll element[N];

ll tree[4 * N], tree_left[4 * N], tree_right[4 * N],
 delta_set[4 * N], delta_add[4 * N];
ll tree_sum[4 * N];

ll inline modify(int a, int b, ll x, int l, int r)
{
    //如果是区间值修改为：
    //(std::min(b, r) - std::max(a, l)) * x;
    return (std::min(b, r) - std::max(a, l) + 1) * x;
}

void inline push_down(int l, int r, int k)
{
    if (delta_set[k] != -1) {
        delta_set[2 * k + 1] = delta_set[k];
        tree[2 * k + 1] = modify(l, (l + r) / 2,  delta_set[k], l, (l + r) / 2);

		//区间点的时候改为modify((l + r) / 2, r, delta_set[k], (l + r) / 2, r);
		//区间点的时候改为tree[2 * k + 2] = delta_set[k];
        if (l != r) {
            delta_set[2 * k + 2] = delta_set[k];
            tree[2 * k + 2] = modify((l + r) / 2 + 1, r, delta_set[k], (l + r) / 2 + 1, r);
        }

        delta_add[2 * k + 1] = delta_add[2 * k + 2] = 0;
        delta_set[k] = -1;
    }

    if (delta_add[k] != 0) {
        delta_add[2 * k + 1] += delta_add[k];
        tree[2 * k + 1] += modify(l, (l + r) / 2,  delta_add[k], l, (l + r) / 2);

		//区间点的时候改为modify((l + r) / 2, r, delta_add[k], (l + r) / 2, r);
		//区间点的时候改为tree[2 * k + 2] += delta_add[k];
        if (l != r) {
            delta_add[2 * k + 2] += delta_add[k];
            tree[2 * k + 2] += modify((l + r) / 2 + 1, r, delta_add[k], (l + r) / 2 + 1, r);
        }

        delta_add[k] = 0;
    }
}

void change_lazy(int a, int b, ll x, int k, int l, int r, bool update)
{
	//区间点的时候改为a>=r||b<=l
    if (a > r || b < l) {
        return ;
    } else if (a <= l && b >= r) {
        //说明整个区间都要被修改，并且覆盖之前的delta
		//这层不需要下放，因为这层的值被修改过了，下次如果查到这层，那么这层的值
		//本来就是正确的。
        if (update) {
            delta_add[k] = 0;
            delta_set[k] = x;
			//区间点的时候改为tree[k] = x;
            tree[k] = modify(a, b, x, l, r);
            tree_sum[k] = tree[k];
            tree_left[k] = tree[k];
            tree_right[k] = tree[k];
        } else {
            delta_add[k] += x;
			//区间点的时候改为tree[k] += x;
            tree[k] += modify(a, b, x, l, r);
        }
	} else {
        //说明标记没有下放，那么就先下放修改
        push_down(l, r, k);

		change_lazy(a, b, x, 2 * k + 1, l, (l + r) / 2, update);
		//区间的时候改为change_lazy(a, b, x, 2 * k + 2, (l + r) / 2, r, update);
		if (l != r)
			change_lazy(a, b, x, 2 * k + 2, (l + r) / 2 + 1, r, update);

        tree[k] = (tree[2 * k + 1] * tree[2 * k + 2]) % BASE;

        tree_sum[k] = tree_sum[2 * k + 1] + tree_sum[2 * k + 2] +
        (tree_right[2 * k + 1] * tree_left[2 * k + 2]) % BASE;
        tree_sum[k] %= BASE;

        tree_left[k] = tree_left[2 * k + 1] +
        (tree[2 * k + 1] * tree_left[2 * k + 2]) % BASE;
        tree_left[k] %= BASE;

        tree_right[k] = tree_right[2 * k + 2] +
        (tree[2 * k + 2] * tree_right[2 * k + 1]) % BASE;
        tree_right[k] %= BASE;
	}
}

ll query_lazy(int a, int b, int k, int l, int r)
{
	//区间点的时候改为a>=r||b<=l
    if (a > r || b < l) {
        return 0;
    } else if (a <= l && b >= r) {
        return tree_sum[k] % BASE;
	} else {
        //下放标记并更新，如果不更新会导致下次查询的时候无法得到正确结果
        push_down(l, r, k);

		ll left = query_lazy(a, b, 2 * k + 1, l, (l + r) / 2);
		ll right = 0;
        //区间的时候改为query_lazy(a, b, 2 * k + 2, (l + r) / 2, r);
		if (l != r)
			right = query_lazy(a, b, 2 * k + 2, (l + r) / 2 + 1, r);

        //所有query本身都不修改线段树的值
        ll sum = left + right + tree_right[2 * k + 1] * tree_left[2 * k + 2];
        return sum;
	}
}

void init(int n)
{
    //delta初始化
    memset(delta_set, -1, sizeof(delta_set));
    memset(delta_add, 0, sizeof(delta_add));
    memset(tree_left, 0, sizeof(tree_left));
    memset(tree_right, 0, sizeof(tree_right));
    //tree自身初始化
    memset(tree, 0, sizeof(tree));
    memset(tree_sum, 0, sizeof(tree_sum));

//	for (int i = 0; i <= n; i++) {
//		change_lazy(i, i, element[i], 0, 0, n, true);
//	}
}

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    int n, q;
    while (scanf("%d %d", &n, &q) != EOF) {
        int t;
        ll x;

        init(n);
        for (int i = 0; i < q; ++i) {
            scanf("%d %lld", &t, &x);
            change_lazy(t, t, x, 0, 1, n, true);

            printf("%lld\n", query_lazy(1, n, 0, 1, n));
        }
    }

    return 0;
}
