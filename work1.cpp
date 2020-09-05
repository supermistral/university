// temp1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

void num3() {
    float b, c;
    cin >> b >> c;
    cout << -c / b;
}

void num2() {
    cout << "Hello World!\n";
    int a, b;
    cin >> a >> b;
    cout << a + b << endl << a - b << endl << a / b << endl;
}

void num4() {
    float a, b, c, d;
    string result;
    cin >> a >> b >> c;
    if (a == 0) {
        cout << -b / c;
    }
    else {
        d = b * b - 4 * a * c;
        if (d == 0) cout << -b / (2 * a);
        else if (d > 0) {
            cout << -b + sqrt(d) / (2 * a) << endl <<  -b - sqrt(d) / (2 * a);
        }
        else cout << "x не существует";
    };
}

void num5() {
    // char x;
    bool street, curtains, lamp;
    cout << "На улице день? 1/0" << endl;
    cin >> street;
    cout << "Шторы раздвинуты?" << endl;
    cin >> curtains;
    cout << "Лампа горит?" << endl;
    cin >> lamp;
    if (street && curtains || lamp) cout << "Светло";
    else cout << "Темно";
}

void num6() {
    float h, R, r, l, V, S;
    cout << "Ввод h, R, r" << endl;
    cin >> h >> R >> r;
    l = sqrt(h * h + (R - r) * (R - r));
    V = 1 / 3 * M_PI * h * (R * R + R * r + r * r);
    S = M_PI * (R * R + l * (R + r) + r * r);
    cout << V << endl << S;
}

void num7() {
    float a, x, res;
    cout << "Ввод a, x" << endl;
    cin >> a >> x;
    x = abs(x);
    if (x < 1) res = sqrt(a * a - x * x);
    else {
        res = a * log(x);
    };
    cout << res;

}

void num8() {
    float x, y, b;
    cout << "Ввод x, y, b" << endl;
    cin >> x >> y >> b;
    cout << log(b - y) * sqrt(b - x);
}

void num9() {
    int n;
    cout << "Ввод N" << endl;
    cin >> n;
    for (int i = 0; i < 10; i++) {
        cout << n + i << endl;
    }
}

void num10_helper(float x) {
    if (x - 1 != 0) {
        cout << x * x - 2 * x + 2 / (x - 1) << endl;
    }
    else cout << "Невозможно вычислить" << endl;
}

void num10() {
    float x = 4;
    for (float i = -4; i <= 4; i += 0.5) {
        cout << i << ") ";
        num10_helper(i);
    }
}

double num11_helper(float S, float p, int n) {
    float r = p / 100;
    float temp = pow(1 + r, n);
    return S * r * temp / (12 * (temp - 1));
}

void num11() {
    float S, p;
    int n;
    cout << "Ввод S, p, n" << endl;
    cin >> S >> p >> n;
    cout << num11_helper(S, p, n) << endl;
}

void num12() {
    float S, n;
    float p = 0;
    double m, m_temp;
    cout << "Ввод S, m, n" << endl;
    cin >> S >> m >> n;
    for (float i = 0; i <= 100; i += 0.01) {
        m_temp = num11_helper(S, i, n);
        if (m_temp == m) {
            p = i * 100;
            break;
        }
    }
    if (p) cout << p;
    else cout << "Не удалось определить p";
}

int main()
{
    setlocale(LC_ALL, "rus");
    //num3();
    //num4();
    //num9();
    //num10();
    num12();
    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
