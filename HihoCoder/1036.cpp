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
static const int M = 1010;
static const int N = 1000010;
static const int CH = 27;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;
static const int MOD = 1000000000 + 7;

class TrieGraph
{
private:
	int trie[N][CH];
	int fail[N];
	int num[N];
	int cur_idx;
	char str_main[N];

public:
	TrieGraph() :cur_idx(1) {
		
	}
	
	void init() {
		memset(trie[0], 0, sizeof(trie[0]));
		cur_idx = 1;
		num[0] = 0;
	}
	
	void insert(char* s) {
		int i = 0, p = 0;
		int len = strlen(s);

		for (i = 0; i <= len - 1; i++)
		{
			int c = s[i] - 'a' + 1;//字符改变时修改
			if (!trie[p][c]){//多串构造，如果只有一个串，这个判断当然没有用
				memset(trie[cur_idx], 0, sizeof(trie[cur_idx]));
				num[cur_idx] = 0;
				trie[p][c] = cur_idx++;
			}
			p = trie[p][c];
		}
		num[p]++;
	}
	
	void build() {
		std::queue<int> q;
		for (int i = 1; i <= CH - 1; i++) {
			if (trie[0][i]) {
				fail[trie[0][i]] = 0;
				q.push(trie[0][i]);
			}
		}

		while (!q.empty())
		{
			int p = q.front();
			q.pop();

			//fail说明
			//可能在父节点的后缀中找到对应字符（父节点后缀本身缺失最后一个字符）。
			//可能没有找到对应字符。既然在这里找不到后缀了，所以就代表肯定不匹配了，那么可以继续回溯。
			for (int i = 1; i <= CH - 1; i++)
			{
				//第1种情况，找到字符，设置fail，继续前进。
				if (trie[p][i])
				{
					int v = trie[p][i];
					q.push(v);
					fail[v] = trie[fail[p]][i];
				}//第2种情况，因为没有找到字符，所以直接回溯
				else
				{
					trie[p][i] = trie[fail[p]][i];
				}
			}
		}
	}

	bool find() {
		int ans = 0, i = 0, p = 0;

		int len = strlen(str_main);
		for (i = 0; i <= len - 1; i++)
		{
			int c = str_main[i] - 'a' + 1;
			p = trie[p][c];
			int tmp = p;
			while (tmp && num[tmp] != -1)
			{
				if (num[tmp] > 0) {
					return true;
				}
				ans += num[tmp];
				num[tmp] = -1;
				tmp = fail[tmp];
			}
		}

		return false;
	}

	char* get_main() {
		return str_main;
	}
};

void solve(int n, TrieGraph* trie_graph)
{
	char str_sub[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", str_sub);
		trie_graph->insert(str_sub);
	}

	scanf("%s", trie_graph->get_main());

	trie_graph->build();

	bool ret = trie_graph->find();

	printf("%s\n", ret == true ? "YES" : "NO");
}

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	int n;
	TrieGraph* trie_graph = new TrieGraph();
	while (scanf("%d", &n) != EOF) {
		trie_graph->init();
		solve(n, trie_graph);
	}

	return 0;
}