#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void print(int* arr, int n) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

void swap(int* arr, int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void shellsort(int* arr, int n) {
    // Шаг сортировки от n/2 до 1
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            for (int j = i; j >= step && arr[j - step] > arr[j]; j -= step) {
                swap(arr, j - 1, j);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int n; cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    shellsort(arr, n);
    print(arr, n);

    return 0;
}
