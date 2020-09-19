#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
using namespace std;

void task1() {
    double h, R, r;
    cout << "Ввод h, R, r" << endl;
    cin >> h >> R >> r;
    if (h > 0 && R > 0 && r > 0) {
        double l = sqrt(h * h + (R - r) * (R - r));
        double V = M_PI * h / 3 * (R * R + R * r + r * r);
        double S = M_PI * (R * R + l * (R + r) + r * r);
        cout << V << endl << S << endl;
    }
    else {
        cout << "Невозможно опеределить объем и площадь" << endl;
    }
}

void task2() {
    float a, x, res;
    cout << "Ввод a, x" << endl;
    cin >> a >> x;
    x = fabs(x);

    if (x >= 1 && a >= x * x) {
        res = sqrt(a - x * x);
    }
    else if (x) {
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
    cout << "Ввод x, y, b" << endl;
    cin >> x >> y >> b;
    if ((b - y) > 0 && (b - x) >= 0) {
        cout << log(b - y) * sqrt(b - x) << endl;
    }
    else {
        cout << "Нет решений" << endl;
    }
}

void task4() {
    int n;
    cout << "Ввод N" << endl;
    cin >> n;
    if (n > 0) {
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
        cout << x * x - 2 * x + 2 / (x - 1) << endl;
    }
    else cout << "Невозможно вычислить" << endl;
}

void task5() {
    for (float i = -4; i <= 4; i += 0.5) {
        cout << i << ") ";
        task5_helper(i);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    task1();
    task2();
    task3();
    task4();
    task5();
    return 0;
}
