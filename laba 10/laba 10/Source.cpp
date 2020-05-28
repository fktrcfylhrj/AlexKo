#include"Header.h"
#include<fstream>
using namespace std;

vector<person> input_group(int n, int k) {
	vector<person> v(n);
	ifstream f("friends.txt"),e("enemy.txt");
	int tmp;
	for (int i = 0; i < n; ++i) {//заполняем друзей
		for (int j = 0; j < n / 2; ++j) {
			f >> tmp;
			v[i].friends.push_back(tmp);
		}
		for (int j = 0; j < k; ++j) {//врагов
			e >> tmp;
			v[i].enemy.push_back(tmp);
		}
		v[i].id = i;
	}
	return v;
}
bool check(person giving, person receiving, int k) {
	if (giving.read == true && receiving.read == false) {
		for (int i = 0; i < k; ++i) {
			if (giving.enemy[i] == receiving.id)
				return false;
		}
		for (int i = 0; i < giving.friends.size(); ++i) {
			if (giving.friends[i] == receiving.id)
				return true;
		}
		return false;
	}
}
vector<person> set_not_read(vector<person> v) {
	for (int i = 0; i < v.size(); ++i) {
		v[i].read = false;
	}
	return v;
}