#include <iostream>
#include <cstdlib>
#include <chrono>


void selection_sort(int*, int);
void exchange_sort(int*, int);
void fill_array(int*, int);
void print_array(int*, int);
void fill_random_array(int*, int, int = 10);
void fill_sorted(int*, int, char);
void insertion_sort(int*, int);
void swap(int*, int, int);

int main()
{
	srand(static_cast<unsigned int>(
		std::chrono::system_clock::now().time_since_epoch().count()
	));

	int length, max;
	std::cout << "Length = "; std::cin >> length;
	std::cout << "Max = "; std::cin >> max;
	int* arr = new int[length];

	fill_random_array(arr, length, max);

	auto begin = std::chrono::steady_clock::now();
	exchange_sort(arr, length);
	auto end = std::chrono::steady_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
	//std::cout << total.count() << " s";

	delete[] arr;
	return 0;
}

void swap(int* arr, int i, int j) {
	int k = arr[i];
	arr[i] = arr[j];
	arr[j] = k;
}

void selection_sort(int* arr, int n) {
	int min;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j)
			if (arr[j] < arr[min])
				min = j;
		swap(arr, min, i);
	}
}

void exchange_sort(int* arr, int n) {
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n - i - 1; ++j)
			if (arr[j] > arr[j + 1])
				swap(arr, j, j + 1);
}

void insertion_sort(int* arr, int n) {
	int x, j;
	for (int i = 1; i < n; ++i) {
		x = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > x; --j)
			arr[j + 1] = arr[j];
		arr[j + 1] = x;
	}
}

void fill_array(int* arr, int n) {
	std::cout << "Fill: ";
	for (int i = 0; i < n; ++i)
		std::cin >> arr[i];
}

void print_array(int* arr, int n) {
	for (int i = 0; i < n; ++i)
		std::cout << arr[i] << " ";
	std::cout << "\n\n";
}

void fill_random_array(int* arr, int n, int max) {
	for (int i = 0; i < n; ++i)
		arr[i] = rand() % max;
}

void fill_sorted(int* arr, int n, char sym) {
	switch (sym) {
	case '+':
		for (int i = 0; i < n; ++i)
			arr[i] = i;
		return;
	case '-':
		for (int i = 0; i < n; ++i)
			arr[i] = n - i - 1;
		return;
	}
}
