
#include <iostream>

using namespace std;




int main()
{
	setlocale(LC_ALL, "russian");
	/*
	cout << "введите количество дней ";
	int  n;
	cin >> n;

	int *arr=new int [n];
	for (int i = 0; i < n; ++i) {
		cout << "введите стоимость акций в день " << i+1<<endl;
		cin >> arr[i];
	}
	int day1, day2,diff=0,day_buf1,day_buf2,dif_buf=-1;
	for (int i = 0; i < n-1; ++i) {
		day1 = i;
		for (int j = i + 1; j < n;++j) {
			day2 = j;
			diff = arr[j] - arr[i];
			if (diff > dif_buf) {
				dif_buf = diff;
				day_buf1 = day1;
				day_buf2 = day2;
			}
		}
	}
	cout << "купить в день " << day_buf1+1 << " продать в день "<<day_buf2+1<<endl;
	cout << "прибыль=" << dif_buf;
	*/
	
	cout << "введите количество ступенек ";
	int  n;
	cin >> n;
	double *arr = new double[n + 1];
	double *arr1 = new double[n];
	arr[n + 1] = 100;
	for (int i = 0; i < n; ++i) {
		cout << "введите вероятность (%) того что ступенька НЕ сломается для ступеньки " << i << endl;
		cin >> arr[i];
	}
	int  mul = 1; int j = 0; int i;

	if (arr[0] > arr[1] && arr[0] > arr[2]) {
		arr1[0] = arr[0];
		i = 0;
	}
	else if (arr[1] > arr[0] && arr[1] > arr[2]) {
		arr1[0] = arr[1];
		i = 1;
	}
	else if (arr[2] >= arr[0] && arr[2] >= arr[1]) {
		arr1[0] = arr[2];
		i = 2;
	}
	++j;

	for (i; i < n - 3; ++j) {
		if (arr[i + 1] * mul > mul*arr[i + 2] && arr[i + 1] * mul > mul*arr[i + 3]) {
			++i;
			mul *= arr[i];
			arr1[j] = arr[i];
		}
		else {
			if (arr[i+2] * mul > mul*arr[i + 1] && arr[i + 2] * mul > mul*arr[i + 3]) {
				i += 2;
				mul *= arr[i];
				arr1[j] = arr[i];
			}
			else {
				if (arr[i+3] * mul >= mul*arr[i + 2] && arr[i + 3] * mul >= mul*arr[i + 1]) {
					i = i + 3;
					mul *= arr[i];
					arr1[j] = arr[i];
				}
			}
		}
	}
	if (i < n - 3) {
		if (arr[n - 3] > arr[n - 2] && arr[n - 3] > arr[n - 1]) {

			arr1[j] = arr[n - 3];

		}
		else if (arr[n - 2] > arr[n - 3] && arr[n - 2] > arr[n - 1]) {
			arr1[j] = arr[n - 2];

		}
		else if (arr[n - 1] >= arr[n - 3] && arr[n - 1] >= arr[n - 2]) {
			arr1[j] = arr[n - 1];

		}
		for (int i = 0; i <= j; ++i) {
			cout << arr1[i] << "\n";
		}
	}
	cout << endl << "последовательность ступенек\n";
	for (int i = 0; i < j; ++i) {
		cout << arr1[i] << "\n";
	}
	
}