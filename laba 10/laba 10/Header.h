#include <vector>

using namespace std;

struct person {
	vector<int> friends;//����������������� ������ ������
	vector<int> enemy;//����������������� ������ ������
	bool read = false;
	int id;
};


vector<person> input_group(int n, int k);
bool check(person giving, person receiving, int k);