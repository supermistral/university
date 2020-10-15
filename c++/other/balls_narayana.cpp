#include <iostream>
using namespace std;

void swap(int* arr, int i, int j) {
    int k = arr[i];
    arr[i] = arr[j];
    arr[j] = k;
}

int check(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i + 1) return 1;
    }
    return 0;
}

bool check_next(int* arr, int n) {
    int low, high;
    // Первый элемент, меньший предыдущего справа налево
    for (low = n - 2; (low > -1 && arr[low] > arr[low + 1]); low--);
    if (low == -1) return false;
    
    // Первый элемент, больший low справа налево
    for (high = n - 1; arr[high] < arr[low]; high--);
    swap(arr, low, high);

    // сортировка по возрастанию чисел правее изначальной позиции low
    int temp1 = low + 1, temp2 = n - 1;
    while (temp1 < temp2) {
        swap(arr, temp1++, temp2--);
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите n -> "; cin >> n;

    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    int sum = 0;
    sum += check(a, n);
    while (check_next(a, n)) {
        sum += check(a, n);
    }
    cout << sum;

    return 0;
}
