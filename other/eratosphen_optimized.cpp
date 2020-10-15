#include <iostream>
#include <ctime>
using namespace std;

void eratosphen(long long x) {
    bool* arr = new bool[x];
    arr[0] = arr[1] = false;
    arr[2] = true;

    clock_t t1 = clock();
    for (long long i = 3ll; i <= x; i++) {
        if (i % 2 == 0) {
            arr[i] = false;
        }
        else {
            arr[i] = true;
        }
    }
    t1 = clock() - t1;
    //cout << "fill " << (double)t1 / ((double)CLOCKS_PER_SEC) << endl;

    clock_t t2 = clock();
    for (long long i = 2ll; i * i <= x; i++) {
        if (arr[i]) {
            for (long long j = i * i; j <= x; j += i) {
                arr[j] = false;
            }
        }
    }
    t2 = clock() - t2;

    //cout << "logic " << (double)t2 / ((double)CLOCKS_PER_SEC) << endl;

    /*for (int i = 2; i < x; i++) {
       if (arr[i]) cout << i << endl;
    }*/
}

int main()
{
    setlocale(LC_ALL, "rus");

    long long border;
    clock_t t;
    cout << "Введите границу -> "; cin >> border;
    for (int i = 0; i < 20; i++) {
        t = clock();
        eratosphen(border);
        t = clock() - t;
        cout << "total " << (double)t / ((double)CLOCKS_PER_SEC) << endl;
    }

    return 0;
}
