#include <iostream>
#include <cstdlib>
#include <chrono>

void fill_array(int*, int);
void print_array(int*, int);
void fill_random_array(int*, int, int = 10);
void exchange_sort_aiverson(int*, int);
void swap(int&, int&);
void shaker_sort(int*, int);
void merge_sort(int*, int, int);
void merge(int*, int, int, int);

int main()
{
    srand(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
    ));

    int length;
    std::cout << "Length = "; std::cin >> length;
    int* arr = new int[length];

    fill_random_array(arr, length);
    print_array(arr, length);
    merge_sort(arr, 0, length - 1);
    print_array(arr, length);

    delete[] arr;
}


void swap(int& elem1, int& elem2) {
    int k = elem1;
    elem1 = elem2;
    elem2 = k;
}

void exchange_sort_aiverson(int* arr, int n) {
    bool isSorted;
    for (int i = 0; i < n - 1; ++i) {
        isSorted = true;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSorted = false;
            }
        }
        if (isSorted)
            break;
    }
}

void shaker_sort(int* arr, int n) {
    int l = 0, r = n - 1;
    bool isSorted = false;
    while (l < r && !isSorted) {
        isSorted = true;
        for (int i = l; i < r; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        --r;
        for (int i = r; i > l; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        ++l;
    }
}

void merge(int* arr, int l, int k, int r) {
    int n1 = k - l + 1;
    int n2 = r - k;
    int* a = new int[n1];
    int* b = new int[n2];

    for (int i = 0; i < n1; ++i)
        a[i] = arr[l + i];
    for (int i = 0; i < n2; ++i)
        b[i] = arr[k + i + 1];

    int i = 0, j = 0, x = l;
    while (i < n1 && j < n2) {
        if (a[i] < b[j])
            arr[x++] = a[i++];
        else
            arr[x++] = b[j++];
    }

    for (; i < n1; ++i, ++x)
        arr[x] = a[i];
    for (; j < n2; ++j, ++x)
        arr[x] = b[j];

    delete[] a, b;
}

void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int k = (r - l) / 2 + l;
        merge_sort(arr, l, k);
        merge_sort(arr, k + 1, r);

        merge(arr, l, k, r);
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
