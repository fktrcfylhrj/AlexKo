#pragma once
#include <iostream>

struct node {
	node* parent;     // указатель на отца
	node* child;      // указатель на одного из сыновей
	node* left;       // указатель на левого брата
	node* right;      // указатель на правого брата
	int degree;       // ранг
	int key;          // числовое значение узла
};
struct fib_heap {
	node* min;        // узел с минимальным корнем
	int roots_amount; // количество узлов
};
bool less(node *, node*);
fib_heap *first(int val);
void add(fib_heap *H, int val);
void out_heap(fib_heap *min);
void pop(fib_heap *H);
void balansirovka(fib_heap *H);