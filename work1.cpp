/ temp1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
    cout << "На улице день? True/False" << endl;
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
    cout << "Ввод h, R, r, l" << endl;
    cin >> h >> R >> r >> l;
    V = 1 / 3 * M_PI * h * (R * R + R * r + r * r);
    S = M_PI * (R * R + l * (R + r) + r * r);
    cout << V << endl << S;
}

void num7() {
    float a, x, res;
    cout << "Ввод a, x";
    cin >> a >> x;
    x = abs(x);
    if (x < 1) res = sqrt(a * a - x * x);
    else {
        res = a * log(x);
    };
    cout << res;

}

int main()
{
    setlocale(LC_ALL, "rus");
    //num3();
    //num4();
    num5();
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
