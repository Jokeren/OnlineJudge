/*
 *	思路1. 枚举所有子串
 *  思路2. 顺序扫描中心点，因为如果在同一个中心点，较短串不是回文子串，那么长串必然不是
 *  思路3. 利用最右对称点，想法来自于连续两次对称，则当前点的对称情况一定和对称点的对称情况有关。
 *  个人感觉HihoCoder上的思路提示反而不是很清楚。
 *	三种情况：
 *	1.最长伸展比当前坐标小，那么当前坐标只能一个个去匹配
 *  2.最长伸展比当前坐标大，那么观察对称点，如果对称点左侧超出当前最长伸展，那么记为右侧的值。
 *	3.否则，记为左侧的值
 *  思路4. 统一奇数长度和偶数长度的解法。因为奇数+偶数（间隔）=奇数，偶数+奇数（间隔）=奇数。
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
static const int M = 300;
static const int N = 1000010;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

char str[2 * N + 1];
char arr[N];
int p[2 * N + 1];

void solve()
{
	scanf("%s", arr);
	int len = strlen(arr);

	str[0] = '#';
	int t = 1;
	for (int i = 0; i < len ; i++){
		str[t++] = arr[i];
		str[t++] = '#';
	}
	str[t] = '\0';

	int mx = 0, id = 0, max = MIN;
	for (int i = 0; i<2 * len + 1; i++){
		p[i] = (mx<i ? 1 : std::min(p[2 * id - i], mx - i));
		
		while (i - p[i] >= 0 && str[p[i] + i] == str[i - p[i]])
			p[i]++;                                 
		if (p[i] + i>mx){                              
			id = i;
			mx = p[i] + i;
		}
		if (p[i]>max){
			max = p[i];
		}
	}
	printf("%d\n", max - 1);
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n;
	while (scanf("%d ", &n) != EOF) {
		for (int i = 0; i < n; i++)
			solve();
	}
	return 0;
}