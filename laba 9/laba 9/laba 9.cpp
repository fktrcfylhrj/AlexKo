
#include"Header.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "russian");
	/*											РЕАЛИЗАЦИЯ ФИББОНАЧИЕВОЙ КУЧИ																*/				
	fib_heap *H=new fib_heap;
	cout << "введите количество элементов кучи n>0\n";
	int n,tmp; cin >> n;
	cout << "введите кучу\n";
	cin >> tmp; 
	H = first(tmp);
	
	for (int i = 1; i < n; ++i) {
		cin >> tmp;
		add(H, tmp);////добавление элемента в кучу
	}

	out_heap(H);//////вывод кучи на экран(сначала выводится корневой узел, и, если у него есть дети, последовательно выводятся дети)
	cout << "\nудаление из кучи элемента с наибольшим приоритетом\n";
	pop(H);
	balansirovka(H);
	out_heap(H);
	return 0;
}

