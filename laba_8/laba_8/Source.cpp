#include<iostream>
#include<stdio.h>
#include"Header.h"
#include<windows.h>
#include<vector>
#define black 1
#define red 0
#define v (char)124
#define br '}'
#define L 'L'
using namespace std;
tree *make_root(int d) {
	tree *tmp = new tree;//*le1=new tree,*le2=new tree;
	//le1->leaf = true; le2->leaf = true; le1->c = black; le2->c = black; le1->l = 0; le1->r = 0; le2->l = 0; le2->r = 0;
	/*	tmp->l = le1; tmp->r = le2;*/ tmp->d = d; tmp->p = 0; tmp->c = black; tmp->l = 0; tmp->r = 0;
	return tmp;
}
tree* pos_search(tree* root, int d) {// возвращает тот после которого вставляем
	tree* temp = root;
	tree* pos = temp;
	while (temp) {
		pos = temp;
		if (d < (temp)->d) { temp = temp->l; }
		else { temp = temp->r; }
	}
	return pos;
}
void rotate_right(tree *n)
{
	tree *pivot = n->l;

	pivot->p = n->p; /* при этом, возможно, pivot становится корнем дерева */
	if (n->p != NULL) {
		if (n->p->l == n)
			n->p->l = pivot;
		else
			n->p->r = pivot;
	}

	n->l = pivot->r;
	if (pivot->r != NULL)
		pivot->r->p = n;

	n->p = pivot;
	pivot->r = n;
}
void rotate_left(tree *n)
{
	tree *pivot = n->r;

	pivot->p = n->p; /* при этом, возможно, pivot становится корнем дерева */
	if (n->p != NULL) {
		if (n->p->l == n)
			n->p->l = pivot;
		else
			n->p->r = pivot;
	}

	n->r = pivot->l;
	if (pivot->l != NULL)
		pivot->l->p = n;

	n->p = pivot;
	pivot->l = n;
}
tree *grandparent(tree *n)
{
	if ((n != NULL) && (n->p != NULL))
		return n->p->p;
	else
		return NULL;
}
tree *uncle(tree *n)
{
	tree *g = grandparent(n);
	if (g == NULL)
		return NULL; // No grandparent means no uncle
	if (n->p == g->l)
		return g->r;
	else
		return g->l;
}
void insert_case5(tree *n)
{
	tree *g = grandparent(n);

	n->p->c = black;
	g->c = red;
	if ((n == n->p->l) && (n->p == g->l)) {
		rotate_right(g);
	}
	else { /* (n == n->p->r) && (n->p == g->r) */
		rotate_left(g);
	}
}
void insert_case4(tree *n)
{
	tree *g = grandparent(n);

	if ((n == n->p->r) && (n->p == g->l)) {
		rotate_left(n->p);
		n = n->l;
	}
	else if ((n == n->p->l) && (n->p == g->r)) {
		rotate_right(n->p);
		n = n->r;
	}
	insert_case5(n);
}
void insert_case3(tree *n)
{
	tree *u = uncle(n), *g;

	if ((u != NULL) && (u->c == red)) {
		// && (n->p->c == red) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
		n->p->c = black;
		u->c = black;
		g = grandparent(n);
		g->c = red;
		insert_case1(g);
	}
	else {
		insert_case4(n);
	}
}
void insert_case1(tree *n)
{
	if (n->p == NULL)
		n->c = black;
	else
		insert_case2(n);
}	  
void insert_case2(tree *n)
{
	if (n->p->c == black)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}
tree *add(tree *root, int n) {
	int d;
	for (int i = 1; i < n; ++i) {
		cout << "введите " << i << "-й элемент: ";
		cin >> d;
		tree *buf = new tree;//,*le1 = new tree, *le2 = new tree;
	//	le1->leaf = true; le2->leaf = true; le1->c = black; le2->c = black; le1->l = 0; le1->r = 0; le2->l = 0; le2->r = 0;
		buf->c = red; buf->d = d; buf->l = 0; buf->r = 0;
		tree *p = pos_search(root, d);
		buf->p = p;
		if (d < p->d) p->l = buf;
		else p->r = buf;
		insert_case1(buf);
		//////////////////
		if (root->p != 0)
			root = root->p;
	}
	return root;
}
void recout(tree *root) {
	if (root) {
		recout(root->l);
		cout << " " << root->d;
		recout(root->r);
	}
}
void symOut(tree *t) {
	while (t->p != 0) {
		t = t->p;//ищем истинный корень
	}
	recout(t);
}
tree *find(tree *root,int d) {
	while (true) {
		if (root->d == d)
			return root;
		if (d < root->d)
			if (root->l != 0)
				root = root->l;
			else
				return 0;
		if (d > root->d)
			if (root->r != 0)
				root = root->r;
			else
				return 0;
	}
}
void prwa(tree* root) {
	if (root!=0) {
		cout << root->d << " ";
		if (root->l != 0)
			prwa(root->l);
		if (root->r != 0)
			prwa(root->r);
	}
}
void powarec(tree *root) {
	if(root->l!=0)
		powarec(root->l);
	cout << root->d<<" ";
	if(root->r!=0)
		powarec(root->r);
}
void powa(tree *root) {
	if (root->l != 0)
		powarec(root->l);
	if (root->r != 0)
		powarec(root->r);
	cout << root->d;
}
int deno(tree *t) {
	int num = 0;
	while (t->p != 0) {
		++num;
		t = t->p;
	}
	return num;
}

int outcolor(tree *t) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (t->c == red) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);//красный шрифт
	}
	else
		SetConsoleTextAttribute(handle, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);//чёрный шрифт
	return t->d;
}
void recout(tree *l, tree *r, int count) {//count - счетчик
	cout << endl;
	cout << " " << br;
	cout << "L:" << outcolor(l);
}
void out(tree *root) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
/*серый шрифт на белом фоне*/
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	cout << L ;   cout << outcolor(root);// вывели корень
	/////////////////////////////////////////////старая версия вывода, которую я не доделал, а удалять жалко
}
void print_tree(tree *top, int level) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	if (top!=0) {
		if(top->l!=0)
		print_tree(top->l, level + 1);
		for (int i = 0; i < level; ++i)
			cout << " ";
		cout << outcolor(top) << endl;
		if(top->r!=0)
		print_tree(top->r, level + 1);
	}
}
tree *
	sibling(tree *n)
{
	if (n == n->p->l)
		return n->p->r;
	else
		return n->p->l;
}
void
replace_node(tree* n, tree* child) {
	child->p = n->p;
	if (n == n->p->l) {
		n->p->l = child;
	}
	else {
		n->p->r = child;
	}
}



void delete_case6(tree *n)
{
	tree *s = sibling(n);

	s->c = n->p->c;
	n->p->c = black;

	if (n == n->p->l) {
		s->r->c = black;
		rotate_left(n->p);
	}
	else {
		s->l->c = black;
		rotate_right(n->p);
	}
}
void delete_case5(tree *n)
{
	tree *s = sibling(n);

	if (s->c == black) { 
		if ((n == n->p->l) &&
			(s->r->c == black) &&
			(s->l->c == red)) { /* this last test is trivial too due to cases 2-4. */
			s->c = red;
			s->l->c = black;
			rotate_right(s);
		}
		else if ((n == n->p->r) &&
			(s->l->c == black) &&
			(s->r->c == red)) {/* this last test is trivial too due to cases 2-4. */
			s->c = red;
			s->r->c = black;
			rotate_left(s);
		}
	}
	delete_case6(n);
}
void delete_case4(tree *n)
{
	tree *s = sibling(n);
	bool con = false;
	if (s == 0) {
		con = true;
	}
	else {
		if (s->l == 0 && s->r == 0)
			con = true;
		else {
			if (s->l == 0 && s->r != 0)
				if (s->r->c == black)
					con = true;
			if (s->l != 0 && s->r == 0)
				if (s->l->c == black)
					con = true;
		}
	}
	if (s != 0) {
		if (s->l != 0 && s->r != 0) {
			if (s->l->c == black && s->r->c == black)
				con = true;
		}
	}
	if ((n->p->c == red) &&		con==true) {
		if(s!=0) s->c = red;
		n->p->c = black;
	}
	else
		delete_case5(n);
}
void delete_case3(tree *n)
{
	tree *s = sibling(n);
	bool con = false;
	if (s == 0) {
		con = true;
	}
	else {
		if (s->l == 0 && s->r == 0)
			con = true;
		else {
			if (s->l == 0 && s->r != 0)
				if (s->r->c == black)
					con = true;
			if (s->l != 0 && s->r == 0)
				if (s->l->c == black)
					con = true;
		}		
	}
	if (s != 0) {
		if (s->l != 0 && s->r != 0) {
			if (s->l->c == black && s->r->c == black)
				con = true;
		}
	}
	if ((n->p->c == black) &&	con==true) {
		if(s!=0) s->c = red;
		delete_case1(n->p);
	}
	else
		delete_case4(n);
}
void delete_case2(tree *n)
{
	tree *s = sibling(n);	bool con = true;
	if (s == 0) con = false;
	else if (s->c == black) con = false;
	if (con==true) {
		n->p->c = red;
		if(s!=0) s->c = black;
		if (n == n->p->l)
			rotate_left(n->p);
		else
			rotate_right(n->p);
	}
	delete_case3(n);
}
void
delete_case1(tree *n)
{
	if (n->p != NULL)
		delete_case2(n);
}
tree *true_root(tree* n) {
	if (n->p == 0)
		return n;
	while (n->p != 0) {
		n = n->p;
	}
	return n;
}
tree *del_right(tree *n) {
	tree *tmp = new tree,*par = new tree,*left=new tree,*rson=new tree;
	if ( n->p == 0) {//root
		if (n->r != 0) rson = n->r;
		tmp = n;
		n = n->r;
		while (n->l != 0)
			n = n->l;//самый левый узел правого поддерева
		if (n->r != 0) {
			tree *buf = n->r;
			par = n->p;
			par->l = buf;
			buf->p = par;
			tmp->d = n->d;
		}
		else {
			par = n->p;
			tmp->d = n->d;
			par->l = 0;
		}
		delete n; n = NULL;
		//tmp->l = left;
		return tmp;
	}
	if (n->l == 0 && n->r == 0) {//leaf
		tmp = n;
		while (tmp->p != 0)
			tmp = tmp->p;
		delete_case1(n);
		par = n->p;
		if (n->d < par->d)
			par->l = 0;
		else par->r = 0;
		delete n; n = NULL;
		return tmp;
	}
	if (n->p != 0 && n->r != 0) {//node
		tmp = n;
		tmp = tmp->r;
		while (tmp->l != 0)
			tmp = tmp->l;
		par = n->p;
		if (tmp == tmp->p->r) {
			if(par->d>tmp->d)
				par->l = tmp;
			else par->r = tmp;
			tmp->p = par;
			if (n->l != 0) {
				tmp->l = n->l;
				n->l->p = tmp;
			}
		}
		else {
			tree *buf = tmp->p;
			//tmp->p->l = 0;
			tmp->p = par;
			par->l = tmp;
			if (n->l != 0) {
				tmp->l = n->l;
				tmp->l->p = tmp;
			}
			tmp->r = n->r;
			buf->l = 0;
		}
		
		delete n; n = NULL;
		delete_case1(tmp);
		return tmp;
	}
}
tree *del_left(tree *n) {
	tree *tmp = new tree,*par=new tree,*right=new tree;
	if (n->p == 0) {										//ЕСЛИ КОРЕНЬ
		right = n->r;
		tmp = n;//корень который удаляем
		n = n->l;
		while (n->r != 0)
			n = n->r;//самый правый узел левого поддерева
		if (n->l != 0){
			par = n->p;
			par->l = n->l; n->l->p = par;
		}
		tmp->d = n->d;	
		par = n->p;
		par->r = 0;
		delete n; n = NULL;
		tmp->r = right;
		return tmp;
	}
	if (n->l == 0 && n->r == 0) {							//ЕСЛИ ЛИСТ
		tmp = n;
		while (tmp->p != 0)
			tmp = tmp->p;
		delete_case1(n);
		par = n->p;
		if (n->d < par->d)
			par->l = 0;
		else par->r = 0;
		delete n; n = NULL;

		return tmp;
	}
	if (n->p != 0 && n->l != 0) {	
		par = n->p;
		tmp = n;
		tmp = tmp->l;
		while (tmp->r != 0)
			tmp = tmp->r;
		tmp->p = par;
		tmp->r = n->r;	
		tmp->r->p = tmp;
		if (par->d > tmp->d)
			par->l = tmp;
		else par->r = tmp;

		if (tmp->r != 0)
			tmp->r -> p = tmp;
		if (tmp == tmp->p->r) {		
			tmp->l = tmp->p;
			tmp->l->p = tmp;
		}
		delete n; n = NULL;
		delete_case1(tmp);
		return tmp;
	}
}

tree *delete_longest(tree *root) {
	bool flag = true;
	vector<tree *> vec; vec.push_back(root); int new_s = vec.size(),old_s=0;
	while (flag) {
		for (int i = old_s; i < new_s; ++i) {
			if (vec[i]->l != 0) { vec.push_back(vec.at(i)->l); flag = true; }
			else flag = false;
			if (vec.at(i)->r != 0) {
				vec.push_back(vec.at(i)->r); flag = true;
			}
			else flag = false;
		}
		if (new_s == 1) {
			old_s = 1;
			new_s = 3;
		}
		else {
			old_s = new_s;
			new_s = (vec.size() - 1) * 2;
		}
	}
	tree *tmp = new tree,  *buf=new tree;
	tmp = vec[vec.size()-1];
	while (tmp->p != 0) {
		buf = tmp;
		tmp = tmp->p;
		del_right(buf);
	}
	if (tmp->r != 0)
		buf = tmp->r;
	else
		buf = tmp->l;
	del_right(tmp);
	tmp = true_root(buf);
	return tmp;
}
int heno(tree *t) {
	if (t == 0)
		return 0;
	else
		return 1 + max(heno(t->l), heno(t->r));
}
tree *del_long(tree *t) {
	int l=0, r=0;
	tree *buf = new tree,*root=new tree;
	if (t->l != 0) {
		l = heno(t->l);
	}
	if (t->r != 0) {
		r = heno(t->r);
	}
	if (l >= r) {
		delete t->l;
		t->l = NULL;
		root = t->r;
		
		root->p = NULL;
	}
	else {
		delete t->r; t->r = NULL;
		root = t->l; root->p = NULL;
	}
/*	while (t->l != 0 || t->r != 0) {
		buf = t;
		if (t->l != 0) {
			l = heno(t->l);
		}
		if (t->r != 0) {
			r = heno(t->r);
		}
		if (l >= r)
			t = t->l;
		else
			t = t->r;
		if (t == NULL)
			break;
	}
	t = buf;
	tree *tmp = new tree; 
	while (t->p != 0) {
		tmp = t;
		t = t->p;
		del_right(tmp);
	}
	if (t->l != 0)
		tmp = t->l;
	else
		tmp = t->r;
	del_right(t);*/
	delete_case1(root);
	return true_root(root);
}