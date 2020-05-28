#include <vector>

using namespace std;

struct person {
	vector<int> friends;//идентификационные номера друзей
	vector<int> enemy;//идентификационные номера врагов
	bool read = false;
	int id;
};


vector<person> input_group(int n, int k);
bool check(person giving, person receiving, int k);