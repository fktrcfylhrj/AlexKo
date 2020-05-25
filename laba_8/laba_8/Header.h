#pragma once
;using namespace std;
struct tree {
	tree *p;//parent
	tree *l;//left
	tree *r;//right
	int d;//data
	bool c;//color
//	bool leaf;
};
tree *make_root(int d);
tree *pos_search(tree *root, int d);
void rotate_left(tree *n);
tree *grandparent(tree *n);
tree *uncle(tree *n);
void rotate_right(tree *n);
void insert_case5(tree *n);
void insert_case4(tree *n);
void insert_case3(tree *n);
void insert_case2(tree *n);
void insert_case1(tree *n);
tree *add(tree *root, int n);
int outcolor(tree *t);
void out(tree *root);
void symOut(tree *t);
void recout(tree *root);
tree *find(tree *root,int d);
void prwa(tree* root); 
int deno(tree *t);
int heno(tree *t);
void powa(tree *root);
void print_tree(tree *top,int level);
void delete_case1(tree *n);
tree *true_root(tree* n);
tree *del_right(tree *n);
tree *del_left(tree *n);
tree *delete_longest(tree *root);
tree *del_long(tree *t);