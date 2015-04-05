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
static const int M = 10010;
static const int N = 1000010;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

char search[N];
char word[M];
int next[M];

void kmp_table()
{
	next[0] = -1;

	int len_word = strlen(word);
	int k = 0;
	for (int i = 1; i < len_word; i++) {
		while (k > -1 && word[k] != word[i]) {
			k = next[k];
		}

		next[i] = k; 

		if (k == -1) {
			k = 0;
		} else if (word[k] == word[i]) {
			k++;
		}
	}
}

int kmp_search()
{
	int len_search = 0, len_word = 0;
	int ncount = 0;

	len_search = strlen(search);
	len_word = strlen(word);

	for (int k = -1, i = 0; i < len_search; i++) {
		while (k > -1 && search[i] != word[k + 1]) k = next[k];	
		
		if (word[k + 1] == search[i]) {
			k++;
		}

		if (len_word - 1 == k) {
			k = next[k];
			ncount++;
		}
}

	return ncount;
}

void solve()
{
	scanf("%s %s ", word, search);
	kmp_table();
	printf("%d\n", kmp_search());
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