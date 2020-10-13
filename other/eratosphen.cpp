#include <iostream>
using namespace std;

void eratosphen(int x) {
    x++;
    int* arr = new int[x];
    for (int i = 0; i < x; i++) {
        arr[i] = i;
    }

    for (int i = 2; i < x; i++) {
        if (arr[i]) {
            for (int j = arr[i] * arr[i]; j < x; j += arr[i]) {
                arr[j] = 0;
            }
        }
    }

    for (int i = 2; i < x; i++) {
        if (arr[i]) cout << arr[i] << endl;
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
