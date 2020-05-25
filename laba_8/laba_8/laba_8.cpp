
#include <iostream>
#include "Header.h"
;using namespace std;
;int n;

int main()
{
	system("color F0");
	setlocale(LC_ALL, "russian");
	cout << "Реализация красно-чёрного дерева. Вариант 10\n";
	/*						ДЕМОНСТРАЦИЯ РАБОТЫ ДЕРЕВА				*/		
	tree *root = make_root(1);////создали первый элемент со значением 1
	root = add(root, 10);
	print_tree(root, 0);
	cout << "\nПрямой обход:\n";
	prwa(root);
	cout << "\nОбратный обход:\n";
	powa(root);
	cout << "\nсимметричный обход:\n";
	symOut(root);
	cout << endl << "поиск элементов со значениями 2 и 100\n";
	tree *buf = find(root, 2);//поиск
	if (buf != 0) {
		cout << "введённый элемент найден\n глубина узла = " << deno(buf) << "\nвысота узла = " << heno(buf) << "\nуровень узла = " << heno(root) - deno(buf) << endl;
	}
	else cout << "введённый элемент не найден\n";
	buf = find(root, 100);
	if (buf != 0) {
		cout << "введённый элемент найден\n глубина узла = " << deno(buf) << "\nвысота узла = " << heno(buf) << "\nуровень узла = " << heno(root) - deno(buf) << endl;
	}
	else cout << "введённый элемент не найден\n";
	cout << "правое удаление элемента с ключом 1\n";
	buf = find(root, 1);
	root = true_root(del_right(buf));
	print_tree(root, 0);
	cout << "левое удаление элемента с ключом 10\n";
	buf = find(root, 10);
	if (buf != 0) {
		root = true_root(del_left(buf));
	}
	print_tree(root, 0);
	cout << "\nЗадание для варианта 10:  Найти все вершины дерева, через которые проходит наибольшее количество путей максимальной длины, и удалить их (правым удалением). Выполнить прямой (левый) обход полученного дерева.\n";
	root=del_long(root);
	cout << "\nПрямой обход:\n";
	prwa(root);

	//////////////////////////////////////////////////////				ЭТО РАБОТА ПОЛЬЗОВАТЕЛЯ С ДЕРЕВОМ
/*	cout << "введите количество элементов n>0\n";
	cin >> n;

	cout << "введите 0-й элемент: "; 
	int d;
	cin >> d;
	tree *root = make_root(d);
	root=add(root, n);//добавление
	//out(root);
	print_tree(root,0);
	cout << "\nПрямой обход:\n";
	prwa(root);
	cout << "\nОбратный обход:\n";
	powa(root);
	cout << "\nсимметричный обход:\n";
	symOut(root); int temp; tree *buf;
stde:
	while (true) {
		cout << "\nхотите удалить элемент 1 - да 0 - нет?\n";
		cin >> temp;
		if (temp == 0) break;
		cout << "введите значение удаляемого элемента (левое удаление)   ";
		cin >> temp;
		buf = find(root, temp); if (buf == 0) { cout << "не пыайтесь сломать программу, такого элемента нет\n"; goto stde; }
		root=true_root( del_left(buf));		
		cout << "дерево после удаления\n";
		print_tree(root, 0);

		cout << "\nвведите значение удаляемого элемента (правое удаление)   ";
		cin >> temp;
		buf = find(root, temp); if (buf == 0) { cout << "не пыайтесь сломать программу, такого элемента нет\n"; goto stde; }
		root = true_root(del_right(buf));
		cout << "дерево после удаления\n";
		print_tree(root, 0);
	}
	while (true) {
		cout << "\nвведите число для поиска, определения глубины  высоты и уровня узла\n";
		cin >> temp;
		buf = find(root, temp);//поиск
		if (buf != 0) {
			cout << "введённый элемент найден\n глубина узла = " << deno(buf) << "\nвысота узла = " << heno(buf) << "\nуровень узла = " << heno(root) - deno(buf)<<endl; 
			cout<< "хотите продолжить? 1 - да 0 - нет\n";
		}
		else cout << "введённый элемент не найден\n" << "хотите продолжить? 1 - да 0 - нет\n";
		cin >> temp;
		if (temp == 0) break;		
	}
	*/
}
