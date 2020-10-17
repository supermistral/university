#include <iostream>

using namespace std;

int evklid(int x, int y) {
    while (x != 0 && y != 0) {
        if (x > y) {
            x %= y;
        }
        else {
            y %= x;
        }
    }
    return x + y;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int x, y;
    cout << "Ввод 1-ого числа -> "; cin >> x;
    cout << "Ввод 2-ого числа -> "; cin >> y;
    cout << "НОД = " << evklid(abs(x), abs(y));

    return 0;
}
