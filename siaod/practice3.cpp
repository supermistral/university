#include <iostream>
#include <ctime>
#include <cstdlib>


void selection_sort(int*, int);
void fill_array(int*, int);
void print_array(int*, int);
void fill_random_array(int*, int);

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	int length;
	std::cout << "Length = "; std::cin >> length;
	int* arr = new int[length];

	fill_random_array(arr, length);
	selection_sort(arr, length);
	print_array(arr, length);
}

void selection_sort(int* A, int n) {
	int min, k;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j)
			if (A[j] < A[min])
				min = j;
		k = A[i];
		A[i] = A[min];
		A[min] = k;
	}
}

void fill_array(int* arr, int n) {
	std::cout << "Fill: ";
	for (int i = 0; i < n; ++i)
		std::cin >> arr[i];
}

void print_array(int* arr, int n) {
	std::cout << "\n";
	for (int i = 0; i < n; ++i)
		std::cout << arr[i] << " ";
}

void fill_random_array(int* arr, int n) {
	for (int i = 0; i < n; ++i)
		arr[i] = rand() % 10;
	print_array(arr, n);
}
