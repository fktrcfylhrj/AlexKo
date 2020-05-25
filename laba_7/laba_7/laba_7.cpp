#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

int sizet;

bool *full; int*hashTable;
const int c = 3;//c – константа, определяющая шаг перебора.

int hashf(int val) {//хеш-функция -сумма квадратов цифр
	int sum=0, buf;
	while (val !=0) {
		buf = val % 10;
		sum = sum + buf * buf;
		val /= 10;
	}
	return sum;
}
void add(int val) {
	int i=hashf(val);//индекс в хеш-таблице
	int j = 0; 
m1:
	i = i + j * c;//линейное опробование
m2:
	if (full[i] == 0) {
		hashTable[i] = val;
		full[i] = 1;
	}
	else {
		j++;
		if (i + j*c > sizet) {
			i = (i + c * j) % sizet;
			j = 0;
			goto m2;
		}
		goto m1;
	}
}
int find(int val) {
	int i=hashf(val);
	int k = 0;
m1:
	i = i + c * k;
m2:
	if (hashTable[i] == val) {
		return i;
	}
	else if (full[i] == false) {
		return -1;
	}
	else if (hashTable[i] != val) {
		k++;
		if (i + c * k  > sizet) {
			i = (i + c * k ) % sizet;
			k = 0;
			goto m2;
		}
		goto m1;
	}
}
int main() {

	setlocale(LC_ALL, "russian");
	int *arr,n;
	cout << "введите количество элементов n>0\n";
	cin >> n; arr = new int[n];
	for (int i = 0; i < n; ++i) {
		arr[i] = rand();//массив из случайных чисел
	}
	cout << arr[n / 4] << " " << arr[n / 2] << " " << arr[3 * n / 4] << endl;
	cout << "введите размер хеш-таблицы\n";
	cin >> sizet;
	auto start = clock();

	hashTable = new int[sizet]; full = new bool[sizet];
	for (int i = 0; i < sizet; ++i) {
		hashTable[i] = 0;
			full[i] = 0;
	}
	auto end = clock();
	cout << "Заполнение нулями за " << end - start<<endl;
	start = clock();
	for (int i = 0; i < 100; ++i) {
		add(arr[i]);
	}
	 end = clock();
	cout << "first 100 " << end-start<<endl;
	for (int i = 100; i < n-100; ++i) {
		add(arr[i]);
	}
	start = clock();
	for (int i = n-100; i < n; ++i) {
		add(arr[i]);
	}
	cout << "last 100 " << clock() - start<<endl;
	cout << "начинаем поиск\n";
	bool buf;
	while (true) {
		cout << "введите число ";
		int temp,index;
		cin >> temp;
		start = clock();
		index = find(temp);
		end = clock();
		if (index == -1)
			cout << "введённый элемент не найден\n";
		else
			cout << "индекс элемента = " << index << endl;
		cout << "время поиска " << end - start;
		cout << "\nхотите продолжить? 1 - да, 0 - нет";
		cin >> buf;
		if (buf == 0)
			break;
		
	}
	
}