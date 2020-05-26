#pragma once
#include <iostream>

struct node {
	node* parent;     // ��������� �� ����
	node* child;      // ��������� �� ������ �� �������
	node* left;       // ��������� �� ������ �����
	node* right;      // ��������� �� ������� �����
	int degree;       // ����
	int key;          // �������� �������� ����
};
struct fib_heap {
	node* min;        // ���� � ����������� ������
	int roots_amount; // ���������� �����
};
bool less(node *, node*);
fib_heap *first(int val);
void add(fib_heap *H, int val);
void out_heap(fib_heap *min);
void pop(fib_heap *H);
void balansirovka(fib_heap *H);