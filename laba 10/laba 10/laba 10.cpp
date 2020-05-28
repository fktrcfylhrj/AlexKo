#include <vector>
#include"Header.h"
#include <iostream>
using namespace std;
const int n = 10;//количество людей
const int k = 2;
int main()///////////////////////////////////////variant 10
{
	vector<person> group = input_group(n, k);
	int start = 0, end = n - 1;//id первого и последнего людей(могут меняться)
	int pc = 0;//длина текущего пути книги
	vector<int> root;//тут записана последовательность людей
	while (pc != 2) {//начало передачи книги
		group[0].read = true;
		for (int i = 1; i < n; ++i) {
			if (check(group[0], group[i], k)) {				
				group[i].read = true;
				pc = 2;
				root.push_back(0);
				root.push_back(i);
				break;
			}
		}
	}
	while (pc != n) {
		for (int i = 0; i < n; ++i) {
			if (!group[i].read) {
				if (check(group[root[root.size() - 1]], group[i], k)) {//если не читал и если ему может передать последний в очереди
					root.push_back(group[i].id);
					group[i].read = true;
					pc++;
				}
				else {//если не читал и последний в очереди передать не может
					group[root[0]].read = false;//это временно
					group[i].read = true;
					if (check(group[i], group[root[0]],k)) { //проверка можно ли вставить перед первым
						vector<int> tmp=root;
						root.push_back(root[root.size() - 1]);
						for (int a = tmp.size()-1; a>0; --a) {
							root[a] = tmp[a - 1];
						}
						root[0] = group[i].id;
						group[i].read = true;
						group[root[1]].read = true;
						pc++;
					}
					else {
						group[root[0]].read = true;
						group[i].read = false;//вернул всё на круги своя
						for (int j = 0; j < root.size() - 1; ++j) {////можно ли вставить где-то между двумя людьми
							if (check(group[root[j]], group[i], k)) {
								group[i].read = true;
								group[root[j+1]].read = false;
								if (check(group[i], group[root[j + 1]], k)) {
									group[root[j + 1]].read = true;
									root.push_back(root[root.size() - 1]);
									for (int t = root.size() - 2; t > j + 1; --t) {
										root[t] = root[t - 1];
									}
									root[j + 1] = group[i].id;
									pc++;
								}
								else {
									group[i].read = false;
									group[root[j + 1]].read = true;
								}
							}
						}
					}
				}
			}	
		}
	}
	cout << "порядок передачи книги(указываются идентификационные номера людей)\n";
	for (int i = 0; i < n; ++i)
		cout << root[i] << " ";

	
}
