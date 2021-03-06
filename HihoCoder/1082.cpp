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
static const int N = 15;
static const int M = 19;
static const int LEN = 210;
static const int MAX = 0x7fffffff;
static const int GMAX = 0x3f3f3f3f;
static const ll LGMAX = 0x3f3f3f3f3f3f3f3f;
static const int MIN = ~MAX;
static const double EPS = 1e-9;
static const ll BASE = 10007;
static const int CH = 27;

class TrieGraph
{
private:
	int trie[N][CH]; //N是节点数目，子串数*长度
	int fail[N];
	int num[N];
	int cur_idx;
	std::string str_main;
	bool is_build;

public:
	TrieGraph() :cur_idx(1), is_build(false) {
		memset(trie[0], 0, sizeof(trie[0]));
		memset(fail, 0, sizeof(fail));
		memset(num, 0, sizeof(num));

	}

	void init() {
		memset(trie[0], 0, sizeof(trie[0]));
		memset(fail, 0, sizeof(fail));
		memset(num, 0, sizeof(num));
		cur_idx = 1;
		num[0] = 0;
		is_build = false;
	}

	void insert(char* s) {
		int i = 0, p = 0;//p表示层数
		int len = strlen(s);

		for (i = 0; i < len; i++)
		{
		    int c = s[i] >= 'a' ? s[i] - 'a' + 1 : s[i] - 'A' + 1;//字符改变时修改
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
			//num[p] |= num[fail[p]];动态规划时的关键
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

	void find() {
		int ans = 0, i = 0, p = 0;
		if (!is_build) {
            is_build = true;
            build();//竟然忘记调用build了...
		}

		bool flag = false;

        std::vector<int> pos;
		for (i = 0; i < str_main.length(); i++)
		{
			int c = str_main[i] >= 'a'? str_main[i] - 'a' + 1:
			    str_main[i] - 'A' + 1;//字符改变时修改

			while (p && !trie[p][c]) p = fail[p];

			p = trie[p][c];

			if (num[p] > 0) {
                pos.push_back(i - 8);
			}
		}

        int ppos = 0;
        int pmain = 0;
        while (pmain < str_main.length()) {
            if (ppos < pos.size() && pmain == pos[ppos]) {
                printf("fjxmlhx");
                pmain += 9;
                ++ppos;
            } else {
                printf("%c", str_main[pmain]);
                ++pmain;
            }
		}
		printf("\n");
	}

	std::string& get_main() {
		return str_main;
	}
};

int main()
{
    FINPUT("in.txt");
    FOUTPUT("out.txt");

    TrieGraph *trie = new TrieGraph();
    trie->insert("marshtomp");
    while (std::getline(std::cin, trie->get_main())) {
        trie->find();
    }

    return 0;
}
