#include <iostream>

using namespace std;

int gcd1(int x, int y) {
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

int gcd2(int x, int y) {
    while (x != y) {
        if (x > y) {
            x -= y;
        }
        else {
            y -= x;
        }
    }
    return x;
}

void handler(int x, int y) {
    char input;
    cout << "Умножением - 1, вычитанием - 2 -> "; cin >> input;
    switch (input) {
        case '1':
            cout << "НОД = " << gcd1(x, y);
        case '2':
            cout << "НОД = " << gcd2(x, y);
        default:
            return false;
    }
    return true;
}

bool check(int x, int y) {
    if (int(x) == x && int(y) == y) {
        return true;
    }
    return false;
}
    

int main()
{
    setlocale(LC_ALL, "rus");

    int x, y;
    bool running = true;
    while (running) {
        cout << "Ввод 1-ого числа -> "; cin >> x;
        cout << "Ввод 2-ого числа -> "; cin >> y;
        if (check(x, y)) {
            running = handler(abs(x), abs(y));
        }
    }

    return 0;
}
