#include <iostream>
using namespace std;

void task1() {
    cout << "Hello world, my name is Mikhail" << endl;
}

void task2() {
    int a, b;
    cout << "Ввод a, b" << endl;
    cin >> a >> b;
    cout << "+: " << a + b << endl;
    cout << "-: " << a - b << endl; 
    cout << "/: " << a / b << endl;
}

// Вспомогательный обработчик b и c
// требуется и в 3 и в 4 задачах
void task3_helper(float b, float c) {
    if (b != 0) cout << -c / b;
    else if (b == 0 && c != 0) cout << "Нет корней";
    else cout << "x - любое";
    cout << endl;
}

void task3() {
    float b, c;
    cout << "Ввод b, c" << endl;
    cin >> b >> c;
    task3_helper(b, c);
}

void task4() {
    float a, b, c, d;
    cout << "Ввод a, b, c" << endl;
    cin >> a >> b >> c;
    if (a == 0) {
        task3_helper(b, c);
    }
    else {
        d = b * b - 4 * a * c;
        if (d == 0) cout << -b / (2 * a);
        else if (d > 0) {
            cout << -b + sqrt(d) / (2 * a) << endl << -b - sqrt(d) / (2 * a);
        }
        else cout << "x не существует";
        cout << endl;
    };
}

void task5() {
    bool street, curtains, lamp;
    cout << "На улице день? 1/0" << endl;
    cin >> street;
    cout << "Шторы раздвинуты?" << endl;
    cin >> curtains;
    cout << "Лампа горит?" << endl;
    cin >> lamp;

    if (street && curtains || lamp) cout << "Светло";
    else cout << "Темно";
    cout << "\n\n";
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
