#include <iostream>

using namespace std;

int eratosphen(int x) {
    int* arr = new int[x];
    for (int i = 0; i < x; i++) {
        arr[i] = i + 2;
    }

    int temp, s;
    for (int i = 0; i < x; i++) {
        s = 2;
        if (arr[i] != 0) {
            temp = arr[i] * s;
            while (temp <= arr[x-1]) {
                arr[temp - 2] = 0;
                s += 1;
                temp = arr[i] * s;
            }
        }
    }

    for (int i = 0; i < x; i++) {
        if (arr[i] != 0) {
            cout << arr[i] << endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    int border;
    cout << "Введите границу -> "; cin >> border;
    eratosphen(border);

    return 0;
}
