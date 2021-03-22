#include <iostream>

void exchange_sort_aiverson(int*, int);
void swap(int&, int&);
void shaker_sort(int*, int);

int main()
{
    
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
