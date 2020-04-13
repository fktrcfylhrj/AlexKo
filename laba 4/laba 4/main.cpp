#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

int arr1[10],arr2[100],arr3[1000],arr4[10000];

void arr_up(int *arr,int n) {
	for (int i = 0; i < n; ++i) {
		arr[i] = i;
	}
}
void arr_down(int *arr, int n) {
	int j = 0;
	for (int i = n-1; i >=0; --i) {
		arr[j] = i;
		++j;
	}
}
void arr_rand(int *arr, int n) {
	for (int i = 0; i < n; ++i) {
		arr[i] = rand();
	}
}
void out_arr(int *arr, int n) {
	cout << endl;
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
}
void sort1(int *arr, int n) {
	int sw = 0;
	unsigned int start_time= clock();
	for (int i = 0; i < n - 1; ++i) {
		int min = i;
		for (int j = i+1; j < n; ++j) {
			if (arr[j] < arr[min])
				min = j;
		}
		swap(arr[i], arr[min]);
		++sw;
	}
	unsigned int end_time = clock();
	cout << "\ntime: " << end_time - start_time;
	cout << "\nswap " << sw;
}
void sort2(int *arr, int n) {
	int sw = 0;
	unsigned int start_time = clock();
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
			swap(arr[j - 1], arr[j]);
			++sw;
		}
	unsigned int end_time = clock();
	cout << "\ntime: " << end_time - start_time;
	cout << "\nswap " << sw;
}
void sort3(int*arr, int n) {
	int sw = 0;
	unsigned int start_time = clock();
	for (int i = 1; i < n; ++i) {
		for (int j = n-1; j >=i; --j) {
			if (arr[j-1] > arr[j]) {
				swap(arr[j], arr[j - 1]);
				++sw;
			}
		}
	}
	unsigned int end_time = clock();
	cout << "\ntime: " << end_time - start_time;
	cout << "\nswap " << sw;
}
int sort4(int *arr, int left, int right)
{
	int sw = 0;
	int pivot; // разрешающий элемент
	int l_hold = left; //лева€ граница
	int r_hold = right; // права€ граница
	pivot = arr[left];
	while (left < right) // пока границы не сомкнутс€
	{
		while ((arr[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			arr[left] = arr[right]; // перемещаем элемент [right] на место разрешающего
			left++; // сдвигаем левую границу вправо
		}
		while ((arr[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			arr[right] = arr[left]; // перемещаем элемент [left] на место [right]
			right--; // сдвигаем правую границу вправо
		}
	}
	arr[left] = pivot; // ставим разрешающий элемент на место
	++sw;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // –екурсивно вызываем сортировку дл€ левой и правой части массива
		sw+=sort4(arr, left, pivot - 1);
	if (right > pivot)
		sw+=sort4(arr, pivot + 1, right);
	return sw;
}
int cmp , sw ;
void msort(int *arr, int lo, int hi, int *cmp, int *sw) {//сортировка сли€нием (пункт 13)
	if (hi <= lo) {
		(*cmp)++;
		return;
	}
	int mid = lo + (hi - lo) / 2;
	msort(arr, lo, mid, cmp, sw);
	msort(arr, mid + 1, hi, cmp, sw);
	int *buf = new int[hi + 1];
	for (int i = 0; i <= hi; ++i) {
		buf[i] = arr[i];
		(*cmp)++;
	}
	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++) {
		(*cmp)++;
		if (i > mid) {
			(*cmp)++;
			arr[k] = buf[j];
			j++;
		}
		else if (j > hi) {
			(*cmp)++;
			arr[k] = buf[i];
			i++;
		}
		else if (buf[j] < buf[i]) {
			(*cmp)++;
			arr[k] = buf[j];
			j++;
		}
		else {
			arr[k] = buf[i];
			i++;
		}
	}
	(*sw)++;
}
int main() {	
	arr_rand(arr4, 10000);
	sort2(arr4, 10000);
	 
	//сортировка сли€нием
	cout << "10 elementov\nup\n";
	arr_up(arr1, 10);
	unsigned int start = clock();
	msort(arr1, 0, 9,&cmp,&sw);
	unsigned int end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start<<endl;
	cout << "down\n";
	arr_down(arr1, 10);
	start = clock();
	msort(arr1, 0, 9,&cmp,&sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "rand\n";
	arr_rand(arr1, 10);
	start = clock();
	msort(arr1, 0, 9,&cmp,&sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;

	cout << "100 elementov\nup\n";
	arr_up(arr2, 100);
	start = clock();
	msort(arr2, 0, 99,&cmp,&sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "down\n";
	arr_down(arr2, 100);
	start = clock();
	msort(arr2, 0, 99,&cmp,&sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "rand\n";
	arr_rand(arr2, 100);
	start = clock();
	msort(arr2, 0, 99,&cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;

	cout << "1000 elementov\nup\n";
	arr_up(arr3, 1000);
	start = clock();
	msort(arr3, 0, 999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "down\n";
	arr_down(arr3, 1000);
	start = clock();
	msort(arr3, 0, 999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "rand\n";
	arr_rand(arr3, 1000);
	start = clock();
	msort(arr3, 0, 999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;

	cout << "10000 elementov\nup\n";
	arr_up(arr4, 10000);
	start = clock();
	msort(arr4, 0, 9999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "down\n";
	arr_down(arr4, 10000);
	start = clock();
	msort(arr4, 0, 9999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	cout << "rand\n";
	arr_rand(arr4, 10000);
	start = clock();
	msort(arr4, 0, 9999, &cmp, &sw);
	end = clock();
	cout << "compare: " << cmp << "\nswap: " << sw << endl;
	cmp = 0; sw = 0;
	cout << "time: " << end - start << endl;
	
	
//10
		arr_up(arr1, 10);
	cout << "sortirovka vyborom:\n";
	cout <<"\n dlya 10 elementov:\n";
	
	 
	sort1(arr1, 10);
	 
	cout << endl <<"up \n";

		arr_down(arr1, 10);
	 
	sort1(arr1, 10);
	 
	cout << endl << "down \n"  ;

		arr_rand(arr1, 10);
	 
	sort1(arr1, 10);
	 
	cout << endl <<"rand \n";
//100
	arr_up(arr2, 100);
	cout << "\ndlya 100 elementov:\n";
	 
	sort1(arr2, 100);
	 
	cout << endl << "up \n"  ;

	arr_down(arr2, 100);
	 
	sort1(arr2, 100);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr2, 100);
	 
	sort1(arr2, 100);
	 
	cout << endl << "rand \n"  ;
//1000
	arr_up(arr3, 1000);
	cout << "\ndlya 1000 elementov:\n";
	 
	sort1(arr3, 1000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr3, 1000);
	 
	sort1(arr3, 1000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr3, 1000);
	 
	sort1(arr3, 1000);
	 
	cout << endl << "rand \n"  ;
//10000
	arr_up(arr4, 10000);
	cout << "\ndlya 10000 elementov:\n";
	 
	sort1(arr4, 10000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr4, 10000);
	 
	sort1(arr4, 10000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr4, 10000);
	 
	sort1(arr4, 10000);
	 
	cout << endl << "rand \n"  ;

	//10
	arr_up(arr1, 10);
	cout << "\nsortirovka vstavkami:\n";
	cout << "\n dlya 10 elementov:\n";

	 
	sort2(arr1, 10);
	 
	cout << endl << "up \n"  ;

	arr_down(arr1, 10);
	 
	sort2(arr1, 10);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr1, 10);
	 
	sort2(arr1, 10);
	 
	cout << endl << "rand \n"  ;
	//100
	arr_up(arr2, 100);
	cout << "\ndlya 100 elementov:\n";
	 
	sort2(arr2, 100);
	 
	cout << endl << "up \n"  ;

	arr_down(arr2, 100);
	 
	sort2(arr2, 100);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr2, 100);
	 
	sort2(arr2, 100);
	 
	cout << endl << "rand \n"  ;
	//1000
	arr_up(arr3, 1000);
	cout << "\ndlya 1000 elementov:\n";
	 
	sort2(arr3, 1000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr3, 1000);
	 
	sort2(arr3, 1000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr3, 1000);
	 
	sort2(arr3, 1000);
	 
	cout << endl << "rand \n"  ;
	//10000
	arr_up(arr4, 10000);
	cout << "\ndlya 10000 elementov:\n";
	 
	sort2(arr4, 10000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr4, 10000);
	 
	sort2(arr4, 10000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr4, 10000);
	 
	sort2(arr4, 10000);
	 
	cout << endl << "rand \n"  ;

//10
	arr_up(arr1, 10);
	cout << "\nsortirovka obmenom:\n";
	cout << "\n dlya 10 elementov:\n";

	 
	sort3(arr1, 10);
	 
	cout << endl << "up \n"  ;

	arr_down(arr1, 10);
	 
	sort3(arr1, 10);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr1, 10);
	 
	sort3(arr1, 10);
	 
	cout << endl << "rand \n"  ;
	//100
	arr_up(arr2, 100);
	cout << "\ndlya 100 elementov:\n";
	 
	sort3(arr2, 100);
	 
	cout << endl << "up \n"  ;

	arr_down(arr2, 100);
	 
	sort3(arr2, 100);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr2, 100);
	 
	sort3(arr2, 100);
	 
	cout << endl << "rand \n"  ;
	//1000
	arr_up(arr3, 1000);
	cout << "\ndlya 1000 elementov:\n";
	 
	sort3(arr3, 1000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr3, 1000);
	 
	sort3(arr3, 1000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr3, 1000);
	 
	sort3(arr3, 1000);
	 
	cout << endl << "rand \n"  ;
	//10000
	arr_up(arr4, 10000);
	cout << "\ndlya 10000 elementov:\n";
	 
	sort3(arr4, 10000);
	 
	cout << endl << "up \n"  ;

	arr_down(arr4, 10000);
	 
	sort3(arr4, 10000);
	 
	cout << endl << "down \n"  ;

	arr_rand(arr4, 10000);
	 
	sort3(arr4, 10000);
	 
	cout << endl << "rand \n"  ;

	//10
	arr_up(arr1, 10);
	cout << "sortirovka bystraya:\n";
	cout << "\n dlya 10 elementov:\n";

	unsigned int start_time = clock();
	cout<<"\nswap: "<<sort4(arr1,0, 10-1);
	unsigned int end_time = clock();
	cout << endl << "up \n"<<end_time-start_time  ;

	arr_down(arr1, 10);
	start_time = clock();
	cout << "\nswap: " << sort4(arr1,0, 10-1);
	end_time = clock();
	cout << endl << "down \n" << end_time - start_time;
	
	arr_rand(arr1, 10);
	start_time = clock();
	cout << "\nswap: " << sort4(arr1,0, 10-1);
	end_time = clock();
	cout << endl << "rand \n" << end_time - start_time;
	//100
	arr_up(arr2, 100);
	cout << "\ndlya 100 elementov:\n";
	start_time = clock();
	cout << "\nswap: " << sort4(arr2,0, 100-1);
	end_time = clock();
	cout << endl << "up \n" << end_time - start_time;

	arr_down(arr2, 100);
	start_time = clock();
	cout << "\nswap: " << sort4(arr2,0, 100-1);
	end_time = clock();
	cout << endl << "down \n" << end_time - start_time;

	arr_rand(arr2, 100);
	start_time = clock();
	cout << "\nswap: " << sort4(arr2, 0,100-1);
	end_time = clock();
	cout << endl << "rand \n" << end_time - start_time;
	//1000
	arr_up(arr3, 1000);
	cout << "\ndlya 1000 elementov:\n";
	start_time = clock();
	cout << "\nswap: " << sort4(arr3, 0,1000-1);
	end_time = clock();
	cout << endl << "up \n" << end_time - start_time;

	arr_down(arr3, 1000);
	start_time = clock();
	cout << "\nswap: " << sort4(arr3, 0,1000-1);
	end_time = clock();
	cout << endl << "down \n" << end_time - start_time;

	arr_rand(arr3, 1000);
	start_time = clock();
	cout << "\nswap: " << sort4(arr3, 0,1000-1);
	end_time = clock();
	cout << endl << "rand \n" << end_time - start_time;
	
	//10000
	
	arr_up(arr4, 10000);
	cout << "\ndlya 10000 elementov:\n";
	start_time = clock();
	cout << "\nswap: "<< sort4(arr4,0, 9999);
	end_time = clock();
	cout << endl << "up \n" << end_time - start_time;

	arr_down(arr4, 10000);
	start_time = clock();
	cout << "\nswap: " <<sort4(arr4, 0,9999);
	end_time = clock();
	cout << endl << "down \n" << end_time - start_time;

	arr_rand(arr4, 10000);
	start_time = clock();
	cout << "\nswap: "<< sort4(arr4,0, 9999);
	end_time = clock();
	cout << endl << "rand \n" << end_time - start_time;
	

}