#include <iostream>
#include <cstdlib>
#include <chrono>

void fill_array(int*, int);
void print_array(int*, int);
void fill_random_array(int*, int, int = 10);
void exchange_sort_aiverson(int*, int);
void swap(int&, int&);
void shaker_sort(int*, int);
//void merge_sort(int*, int, int);
void merge_sort(int*, int, int, long long&, long long&);
//void merge(int*, int, int, int);
void merge(int*, int, int, int, long long&, long long&);

int main()
{
    srand(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
    ));

    int length;
    std::cout << "Length = "; std::cin >> length;
    int* arr = new int[length]; 

    fill_random_array(arr, length, length);

    auto begin = std::chrono::steady_clock::now();
    //print_array(arr, length);
    //long long comps = 0, moves = 0;
    //merge_sort(arr, 0, length - 1, comps, moves);
    exchange_sort_aiverson(arr, length);
    //shaker_sort(arr, length);
    //print_array(arr, length);
    auto end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    //std::cout << "Length = " << length << "\n";
    std::cout << total.count() << " ms";
    //std::cout << "Comps: " << comps << "\nMoves: " << moves <<
    //    "\nTotal: " << comps + moves << "\n";

    delete[] arr;
}


void swap(int& elem1, int& elem2) {
    int k = elem1;
    elem1 = elem2;
    elem2 = k;
}

void exchange_sort_aiverson(int* arr, int n) {
    long long comps = 0, moves = 0;
    bool swapFlag = true;
    for (int i = 0; i < n - 1 && swapFlag; ++i) {
        swapFlag = false;
        for (int j = 0; j < n - i - 1; ++j) {
            ++comps;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                ++moves;
                swapFlag = true;
            }
        }
    }
    std::cout << "Comps: " << comps << "\nMoves: " << moves <<
        "\nTotal: " << comps + moves << "\n";
}

void shaker_sort(int* arr, int n) {
    int l = 0, r = n - 1;
    bool swapFlag = true;
    long long comps = 0, moves = 0;

    while (l < r && swapFlag) {
        swapFlag = false;
        for (int i = l; i < r; ++i) {
            ++comps;
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapFlag = true;
                ++moves;
            }
        }
        --r;
        for (int i = r; i > l; --i) {
            ++comps;
            if (arr[i - 1] > arr[i]) {
                swap(arr[i-1], arr[i]);
                swapFlag = true;
                ++moves;
            }
        }
        ++l;
    }
    std::cout << "Comps: " << comps << "\nMoves: " << moves <<
        "\nTotal: " << comps + moves << "\n";
}

//void merge(int* arr, int l, int k, int r) {
void merge(int* arr, int l, int k, int r, long long &comps, long long &moves) {
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
        ++comps; ++moves;
        if (a[i] < b[j])
            arr[x++] = a[i++];
        else
            arr[x++] = b[j++];
    }

    for (; i < n1; ++i, ++x, ++moves)
        arr[x] = a[i];
    for (; j < n2; ++j, ++x, ++moves)
        arr[x] = b[j];

    delete[] a, b;
}

void merge_sort(int* arr, int l, int r, long long &comps, long long &moves) {
    if (l < r) {
        int k = (r + l) / 2;
        merge_sort(arr, l, k, comps, moves);
        merge_sort(arr, k + 1, r, comps, moves);

        merge(arr, l, k, r, comps, moves);
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
