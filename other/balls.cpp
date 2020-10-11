#include <iostream>
using namespace std;

void print(int* a, int n) {
    for (int i = 0; i < n; i++) {
        cout.width(3);
        cout << a[i];
    }
    cout << endl;
}

void swap(int* arr, int i, int j) {
    int k = arr[i];
    arr[i] = arr[j];
    arr[j] = k;
}

bool check(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i + 1) return true;
    }
    return false;
}

int perm(int* arr, int n, int start) {
    int sum = 0;
    if (start == n) {
        //print(arr, n);
        if (check(arr, n)) {
            return 1;
        }
    }
    else {
        for (int i = start; i < n; i++) {
            swap(arr, i, start);
            sum += perm(arr, n, start + 1);
            swap(arr, i, start);
        }
    }
    return sum;
}

int main()
{
    int n;
    cout << "Введите n -> "; cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    cout << perm(a, n, 0);

    return 0;
}
