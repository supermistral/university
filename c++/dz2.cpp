#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
using namespace std;

void task1() {
    float h, R, r;
    cout << "Введите h -> ";  cin >> h;
    cout << "Введите R -> ";  cin >> R;
    cout << "Введите r -> ";  cin >> r;

    if (h > 0 && R > 0 && r > 0) {
        if (R < r) {
            cout << "Конус перевернутый" << endl;
            return;
        }
        double l = sqrt(h * h + (R - r) * (R - r));
        cout << "V = " << M_PI * h * 1.0 / 3.0 * (R * R + R * r + r * r) << endl;
        cout << "S = " << M_PI * (R * R + l * (R + r) + r * r) << endl;
    }
    else {
        cout << "Невозможно опеределить объем и площадь" << endl;
    }
}

void task2() {
    float a, x;
    double res;
    cout << "Введите a -> ";  cin >> a;
    cout << "Введите x -> ";  cin >> x;
    x = fabs(x);

    if (x >= 1 && a >= x * x) {
        res = sqrt(a - x * x);
    }
    else if (x < 1 && x != 0) {
        res = a * log(x);
    }
    else {
        cout << "Нет решений" << endl;
        return;
    }
    cout << res << endl;

}

void task3() {
    float x, y, b;
    cout << "Введите x -> ";  cin >> x;
    cout << "Введите y -> ";  cin >> y;
    cout << "Введите b -> ";  cin >> b;

    if ((b - y) > 0 && (b - x) >= 0) {
        cout << log(b - y) * sqrt(b - x) << endl;
    }
    else {
        cout << "Нет решений" << endl;
    }
}

void task4() {
    float n;
    cout << "Введите N -> ";  cin >> n;

    if (n > 0 && (int(n) - n) == 0) {
        for (int i = 0; i < 10; i++) {
            cout << n + i + 1 << endl;
        }
    }
    else {
        cout << "Число не натуральное" << endl;
    }
}

// Обработчик для "Табуляции"
// Функция, вызываемая на каждой итерации
void task5_helper(float x) {
    if (x - 1 != 0) {
        cout << "y = " << x * x - 2 * x + 2 / (x - 1) << endl;
    }
    else cout << "Невозможно вычислить" << endl;
}

void task5() {
    for (int i = -4; i <= 4; i += 2) {
        cout << "x = " << i << " -> ";
        task5_helper(i);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    task1();
    task2();
    //task3();
    task4();
    task5();
    return 0;
}
