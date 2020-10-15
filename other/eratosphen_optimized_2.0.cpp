#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

void eratosphen(long long x) {
    long long n = (x + 1) / 2;
    long long sqrtX = sqrt(x);
    bool* arr = new bool[n];

    // 1 элемент не затрагивается (это вымышленная 2), остальные - нечетные (1: 3; 2: 5; 3: 7; 4: 9 ...)
    for (long long i = 0; i < n; i++) {
        arr[i] = true;
    }

    long long temp;
    for (long long i = 1; (i * 2 + 1) <= sqrtX; i++) {
        if (arr[i]) {
            temp = (i * 2 + 1);
            for (long long j = temp * temp; j <= x; j += (temp * 2)) {
                arr[(j - 1) / 2] = false;
            }
        }
    }

    /*cout << 2 << endl;
    for (int i = 1; i < n; i++) {
        if (arr[i]) {
            cout << i * 2 + 1 << endl;
        }
    }*/
    delete[] arr;
}

int main()
{
    setlocale(LC_ALL, "rus");

    long long border;
    clock_t t;
    cout << "Введите границу -> "; cin >> border;
    for (int i = 0; i < 100; i++) {
        t = clock();
        eratosphen(border);
        t = clock() - t;
        cout << "total " << (double)t / ((double)CLOCKS_PER_SEC) << endl;
    }

    return 0;
}
