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
static const int N = 100010;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

struct trie{
	struct trie *child[27];
	int ncount;
	char letter;
}*root;

char dict[N];

void inline trie_build(char *str, int len)
{
	struct trie *prev = root;
	for (int i = 0; i < len; i++) {
		int tmp = str[i] - 'a';
		if (prev->child[tmp] == NULL) {
			prev->child[tmp] = (struct trie *) malloc(sizeof(struct trie));
			memset(prev->child[tmp], 0, sizeof(struct trie));
			prev->child[tmp]->letter = str[i];
		}
		prev->child[tmp]->ncount++;
		prev = prev->child[tmp];
	}
}

int inline trie_search(char *word, int len)
{
	struct trie *prev = root;
	for (int i = 0; i < len; i++) {
		int tmp = word[i] - 'a';
		if (prev->child[tmp] == NULL) {
			return 0;
		}
		else {
			prev = prev->child[tmp];
		}
	}

	return prev->ncount;
}
void solve(int n)
{
	root = (struct trie *) malloc(sizeof(struct trie));
	memset(root, 0, sizeof(struct trie));

	for (int i = 0; i < n; i++) {
		scanf("%s", dict);
		trie_build(dict, strlen(dict));
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		scanf("%s", dict);
		printf("%d\n", trie_search(dict, strlen(dict)));
	}
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n;
	while (scanf("%d ", &n) != EOF) {
		solve(n);
	}
	return 0;
}