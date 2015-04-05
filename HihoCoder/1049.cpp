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
static const int M = 100010;
static const int N = 1000;
static const int LEN = 1000010;
static const int MAX = 0x7fffffff;
static const int MIN = ~MAX;
static const double EPS = 1e-7;
static const int base = 10;

char prev[N];
char mid[N];

class Bst{
private:
	struct node{
		node* left;
		node* right;
		int c;
	}tree[N];
	int num_of_node;
public:
	Bst() : num_of_node(0) {

	}
	Bst(int v) :num_of_node(0){
		create(v);
	}

	int get_num_of_node(){
		return num_of_node;
	}

	node* get_root(){
		return &tree[0];
	}

	node* create(int c){
		tree[num_of_node].c = c;
		tree[num_of_node].left = tree[num_of_node].right = NULL;
		return &tree[num_of_node++];
	}

	node *build(node* n, int v){
		if (v>n->c){
			if (n->right == NULL){
				node *t = create(v);
				n->right = t;
				return t;
			}
			else {
				build(n->right, v);
			}
		}
		else if (v<n->c){
			if (n->left == NULL){
				node *t = create(v);
				n->left = t;
				return t;
			}
			else {
				build(n->left, v);
			}
		}
	}


	node* build_pre_mid(int s1, int e1, int s2, int e2){
		node* n = create(prev[s1]);
		int index;
		for (int i = s2; i <= e2; i++){
			if (mid[i] == prev[s1]){
				index = i;
				break;
			}
		}

		if (index > s2){
			n->left = build_pre_mid(s1 + 1, s1 + (index - s2), s2, index - 1);
		}

		if (index < e2){
			n->right = build_pre_mid(s1 + index - s2 + 1, e1, index + 1, e2);
		}

		return n;
	}


	void post_order(node* t){
		if (t->left != NULL){
			post_order(t->left);
		}

		if (t->right != NULL){
			post_order(t->right);
		}

		printf("%c", t->c);
	}

	void pre_order(node* t){
		printf("%d ", t->c);

		if (t->left != NULL){
			pre_order(t->left);
		}

		if (t->right != NULL){
			pre_order(t->right);
		}
	}

	void mid_order(node* t){
		if (t->left != NULL){
			mid_order(t->left);
		}

		printf("%d ", t->c);

		if (t->right != NULL){
			mid_order(t->right);
		}
	}
};

int main()
{
	FINPUT("in.txt");
	FOUTPUT("out.txt");

	
	while (scanf("%s ", prev) != EOF) {
		scanf("%s ", mid);
		Bst bst;
		bst.build_pre_mid(0, strlen(prev) - 1, 0, strlen(mid) - 1);
		bst.post_order(bst.get_root());
		printf("\n");
	}
	return 0;
}