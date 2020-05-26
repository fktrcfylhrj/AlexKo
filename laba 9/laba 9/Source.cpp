#include <iostream>
#include"Header.h"
#include <vector>
using namespace std;

int num_of_bro(node *n) {//количество всех братьев
	node *tmp = n->right;
	int num = 1;
	if (n->right == n)
		return 1;
	if (n->left == tmp && tmp->right == n)
		return 2;
	else {
		num = 2;
		while (tmp->right != n) {
			tmp = tmp->right;
			num++;
		}
	}
	return num;
}
bool less(node *n1, node*n2) {
	if (n1->key < n2->key)
		return true;
	else
	return false;
}
fib_heap *first(int val) {
	
	node *buf=new node; buf->key = val; buf->child = NULL; buf->degree = 0; buf->left = buf; buf->parent = NULL; buf->right = buf;
	fib_heap *H=new fib_heap; H->min = buf; H->roots_amount = 1;
	return H;
}
void link(node *n1, node *n2) {
	if (n1->parent == NULL && n2->parent == NULL && n1->degree == n2->degree && n1!=n2) {
		if (n1->left == n1->right && n2->right == n2->left) {//если их только двое но скорее всего этот случай рассматривать бессмысленно но € оставил,т.к. пока работает лучше ничего не трогать
			n1->left = n1; n1->right = n1; n2->left =n2; n2->right = n2;
			if (n1->key < n2->key) {/////////////////////если приоритет n1 больше
				if (n1->degree == 0) {///////////////////////если у него нет детей, то делаем нового ребЄнка
					n1->child = n2;
					n2->parent = n1;
					n1->degree = 1;
				}
				else {///////////////////////////////////иначе - делаем n2 братом ребЄнка n1
					n2->left->right = n2->right;
					n2->right->left = n2->left;
					n1->child->right->left = n2;
					n2->right = n1->child->right;
					n1->child->right = n2;
					n2->left = n1->child;
					n1->degree++;
				}
			}
			else {////////////////////////////////////если приоритет n2 больше
				if (n2->degree == 0) {///////////////////////если у него нет детей, то делаем нового ребЄнка
					n2->child = n1;
					n1->parent = n2;
					n2->degree = 1;
				}
				else {///////////////////////////////////иначе - делаем n1 братом ребЄнка n2
					n1->left->right = n1->right;
					n1->right->left = n1->left;
					n2->child->right->left = n1;
					n1->right = n2->child->right;
					n2->child->right = n1;
					n1->left = n2->child;
					n2->degree++;
				}
			}
			return;
		}
		else {//////////////////////////если корневых братьев больше чем 2
			if (n1->key <= n2->key) {///////если приоритет n1 больше
				if (n1->child == 0) {////если у n1 нет сына
					n2->left->right = n2->right;
					n2->right->left = n2->left;
					n2->left = n2;
					n2->right = n2;
					n1->child = n2;
					n1->degree = 1;
					n2->parent = n1;
				}
				else {
					n2->left->right = n2->right;
					n2->right->left = n2->left;
					n2->right = n1->child->right;
					n1->child->right->left = n2;
					n2->left = n1->child;
					n1->child->right = n2;		
					n1->degree++;
				}
			}
			else {//////////////////////////////если приоритет n2 больше
				n1->left->right = n1->right;
				n1->right->left = n1->left;
				if (n2->child == 0) {
					n2->child = n1;
					n2->degree = 1;
					n1->parent = n2;
					n1->left = n1;
					n1->right = n1;
				}
				else {
					n1->right = n2->child->right;
					n2->child->right->left = n1;
					n1->left = n2->child;
					n2->child->right = n1;
					n2->degree++;
				}
			}
		}
	}
}
void cut(node *min, node *n) {
	if (n->left == n && n->right == n) {
		n->parent->child = NULL;
		n->parent = NULL;
	}
	else {
		n->right->parent = n;
		n->child = n->right;
		n->right->left = n->left;
		n->left->right = n->right;
		n->degree++;
		n->parent = NULL;
	}
	min->left->right = n;
	n->left = min->left;
	min->left = n;
	n->right = min;
}
void add(fib_heap *H, int val) {
	node *tmp = new node; tmp->child = NULL; tmp->parent = NULL; tmp->key = val; tmp->degree = 0;
	if (val < H->min->key) {
		H->min->right->left = tmp;
		tmp->right = H->min->right;
		H->min->right = tmp;
		tmp->left = H->min;
		H->min = tmp;
	}
	else {
		H->min->right->left = tmp;
		tmp->right = H->min->right;
		H->min->right = tmp;
		tmp->left = H->min;
	}
m:
	vector<node *> v; node *buf = new node; buf = H->min;
	int num = num_of_bro(H->min);
	for (int i = 0; i < num; ++i) {
		v.push_back(buf);
		buf = buf->right;
	}
	for (int i = 0; i < num-1; ++i) {
		for (int j = i+1; j < num; ++j) {
			if (v[i]->degree == v[j]->degree) {
				link(v[i], v[j]);
				goto m;
			}
		}
	}
	/*
	link(H->min, H->min->right);
	node *start = H->min->right, *end = H->min;
	while (end != start) {
		int num = num_of_bro(start); node* cur = start->right;
		for (num; num > 0; --num) {
			
				link(start, cur);
				if (start->parent != 0)
					start = H->min->right;
				if (cur->parent != 0)
					cur = start->right;
			if (start->parent != 0 || cur->parent != 0)
				break;
			else {
				cur = cur->right;
			}
		}
		start = start->right;
	}
	*/
	//node *cur = new node;//*min = new node;
	//cur = H->min->right;
	//tmp = H->min;
	/*
	for (cur=tmp->right; cur != tmp && cur->degree == H->min->degree;cur=cur->right) {
		for (node *buf = cur->right; buf != cur && cur->degree == buf->degree; buf = buf->right)
			link(buf, cur);
	}*/
/*
		while (tmp->parent==0&&tmp->right!=H->min) {
			node *buf = new node; buf = H->min->right;
			while( buf != H->min) {
				if (tmp->degree == buf->degree&&tmp != buf)
					link(tmp, buf);
			}
		}
		*/
	H->roots_amount++;
}
void out_root(node *n, int bro) {
	vector<node *> v;
	for (int i = 0; i < bro; ++i) {
		v.push_back(n);
		n = n->right;
	}
	for (int i = 0; i < bro; i++) {
		if (v[i]->degree > 0) {
			cout << " потомки узла со значением " << v[i]->key << " : ";
			out_root(v[i]->child, num_of_bro(v[i]->child));
		}
		else {
			cout << v[i]->key << " ; ";
		}
	}

}
void out_heap(fib_heap *min) {
	node *n = new node; n = min->min;
	int num = num_of_bro(n);
	vector<node *> v;
	for (int i = 0; i < num; ++i) {
		v.push_back(n);
		n = n->right;
	}
	for (int i = 0; i < num; ++i) {
		cout << "потомки  ќ–Ќ≈¬ќ√ќ узла со значением " << v[i]->key << " : ";
		if (v[i]->degree > 0) {
			out_root(v[i]->child, num_of_bro(v[i]->child));
			
		}	
		cout << endl;
	}
}
void pop(fib_heap *H) {
	if (H->min->right == H->min && H->min->child == NULL) {
		delete H->min; H->min = NULL;
		delete H; H = NULL;
		return;
	}
	node *newmin = new node, *minbro = NULL, *minch = new node, *tmp = new node; int num;
	if (H->min->right != H->min) {////нвшли минимального брата
		num = num_of_bro(H->min) - 1;
		minbro = H->min->right; tmp = minbro;
		for (int i = 0; i < num; ++i) {
			if (minbro->key > tmp->key)
				minbro = tmp;
			tmp = tmp->right;
		}
	}
	if (H->min->child != 0) {/////нашли минимального ребЄнка
		num = num_of_bro(H->min->child);
		minch = H->min->child; tmp = minch->right;
		for (int i = 0; i < num; ++i) {
			if (minch->key > tmp->key) {
				minch = tmp;
			}
			tmp = tmp->right;
		}
	}
	if (H->min->right == H->min) {
		delete H->min;
		H->min = minch;
		H->roots_amount--;
		return;
	}
	if (H->min->child == NULL) {
		delete H->min;
		H->min = minch;
		H->roots_amount--;
		return;
	}
	if (minbro->key <= minch->key) {
		
		if (minbro->child == 0) {
			minbro->child = H->min->child;
			H->min->child->parent = minbro;
			if (minbro == H->min->right) {
				H->min->left->right = minbro;
				minbro->left = H->min->left;
			}
			else {
				H->min->right->left = minbro;
				minbro->right = H->min->right;
			}
		}
		else {
			minbro->child->right->left = H->min->child;
			H->min->child->right = minbro->child->right;
			minbro->child->right = H->min->child;
			H->min->child->left = minbro->child;
			H->min->child->parent = NULL;
		}
		delete H->min; H->min = NULL;
		H->min = minbro;
	}
	else {
		cut(H->min, minch);
		H->min->right->left = H->min->left;
		H->min->left->right = H->min->right;
		H->min->child = NULL;
		delete H->min; H->min = NULL;
		H->min = minch;
	}
	H->roots_amount--;
}
void balansirovka(fib_heap *H) {
m1:
	vector<node *> v; node *buf = new node; buf = H->min;
	int num = num_of_bro(H->min);
	for (int i = 0; i < num; ++i) {
		v.push_back(buf);
		buf = buf->right;
	}
	for (int i = 0; i < num - 1; ++i) {
		for (int j = i + 1; j < num; ++j) {
			if (v[i]->degree == v[j]->degree) {
				link(v[i], v[j]);
				goto m1;
			}
		}
	}
}