/*
 *	˼·1. ö�������Ӵ�
 *  ˼·2. ˳��ɨ�����ĵ㣬��Ϊ�����ͬһ�����ĵ㣬�϶̴����ǻ����Ӵ�����ô������Ȼ����
 *  ˼·3. �������ҶԳƵ㣬�뷨�������������ζԳƣ���ǰ��ĶԳ����һ���ͶԳƵ�ĶԳ�����йء�
 *  ���˸о�HihoCoder�ϵ�˼·��ʾ�������Ǻ������
 *	���������
 *	1.���չ�ȵ�ǰ����С����ô��ǰ����ֻ��һ����ȥƥ��
 *  2.���չ�ȵ�ǰ�������ô�۲�ԳƵ㣬����ԳƵ���೬����ǰ���չ����ô��Ϊ�Ҳ��ֵ��
 *	3.���򣬼�Ϊ����ֵ
 *  ˼·4. ͳһ�������Ⱥ�ż�����ȵĽⷨ����Ϊ����+ż���������=������ż��+�����������=������
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