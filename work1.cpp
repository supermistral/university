// project1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

// 1 ДЗ: от 1 до 5
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

// 2 ДЗ: от 6 до 10
void task6() {
    float h, R, r, l, V, S;
    cout << "Ввод h, R, r" << endl;
    cin >> h >> R >> r;
    l = sqrt(h * h + (R - r) * (R - r));
    V = 1 / 3 * M_PI * h * (R * R + R * r + r * r);
    S = M_PI * (R * R + l * (R + r) + r * r);
    cout << V << endl << S << endl;
}

void task7() {
    float a, x, res;
    cout << "Ввод a, x" << endl;
    cin >> a >> x;
    x = abs(x);

    if (x < 1) res = sqrt(a * a - x * x);
    else {
        res = a * log(x);
    };
    cout << res << endl;

}

void task8() {
    float x, y, b;
    cout << "Ввод x, y, b" << endl;
    cin >> x >> y >> b;
    cout << log(b - y) * sqrt(b - x) << endl;
}

void task9() {
    int n;
    cout << "Ввод N" << endl;
    cin >> n;
    for (int i = 0; i < 10; i++) {
        cout << n + i << endl;
    }
}

// Обработчик для "Табуляции"
// Функция, вызываемая на каждой итерации
void task10_helper(float x) {
    string result;
    if (x - 1 != 0) {
        cout << x * x - 2 * x + 2 / (x - 1) << endl;
    }
    else cout << "Невозможно вычислить" << endl;
}

void task10() {
    float x = 4;
    for (float i = -4; i <= 4; i += 0.5) {
        cout << i << ") ";
        task10_helper(i);
    }
}

// 3 ДЗ: от 11 до 15
// Обработчик для задач Заем и Ссуда
// функция с возвратом m
double task11_helper(float S, float p, int n) {
    float r = p / 100;
    float temp = pow(1 + r, n);
    return S * r * temp / (12 * (temp - 1));
}

void task11() {
    float S, p;
    int n;
    cout << "Ввод S, p, n" << endl;
    cin >> S >> p >> n;
    cout << task11_helper(S, p, n) << endl;
}

// Бинарный поиск с точностью до 0.001
// Используется функция и возвратом m для вычисления на каждой итерации
void task12() {
    float S, n, p = 0;
    double m, m_temp, step = 0.001, adj = 1 / step;
    cout << "Ввод S, m, n" << endl;
    cin >> S >> m >> n;
    float mid, high = 100, low = 0;

    while (low < high) {
        mid = (high + low) / 2;
        m_temp = task11_helper(S, mid, n);
           
        // Без округления не сравнить дробные числа. При этом нужна корректировка для round
        if (round(m_temp * adj) > round(m * adj)) high = mid - step;
        else if (round(m_temp * adj) < round(m * adj)) low = mid + step;
        else {
            p = mid;
            break;
        }
    }

    if (p) cout << p;
    else cout << "Не удалось определить p";
    cout << endl;
}

// Задачи "Копирование файла" и "фильтр" - одно и то же
// Обработчик для задачи "фильтр" - проверка на числовой тип строки
void task14_helper(string line) {
    int dig;
    for (int i = 0; i < line.length(); i++) {
        dig = line[i];
        if (dig) cout << dig;
    }
}

// Открытие файла и вывод содержимого, требуется в рамках обоих задач
// Аргумент для удобства - чтобы не повторять код в другой задаче и
// вызывать функцию выше, когда нужно
void open(bool cond = false, string file = "D:\\forwork\\for_c.txt") {
    ifstream in(file);
    if (in.is_open()) {
        string line;

        while (getline(in, line)) {
            if (cond) task14_helper(line);
            else cout << line;
            cout << endl;
        }
    }
    in.close();
}

void task13() {
    open();
}

// Вызов открытия файла - предыдущей задачи с аргументом для вызова хелпера
void task14() {
    open(true);
}

// Можно ввести сколь угодно много символов - используются первые 30
// сортировка пузырьком
void task15() {
    const int length = 30;
    char line[length];
    string userLine;
    cout << "Ввод строки" << endl;
    cin >> userLine;

    for (int i = 0; i < length; i++) {
        line[i] = userLine[i];
    }
    cout << "Ваша строка - " << line << endl;

    for (int i = 0; i < length - 1; i++) {
        for (int j = i; j < length - 1 - i; j++) {
            if (line[j] > line[j + 1]) {
                char k = line[j];
                line[j] = line[j + 1];
                line[j + 1] = k;
            }
        }
    }

    for (int i = 0; i < length; i++) cout << line[i];
}
// 4 ДЗ
void task16() {
    string file = "D:\\forwork\\for_16.txt";
    const int len = 10;
    int arr[len];
    ofstream out;

    for (int i = 0; i < len; i++) {
        cout << i << ": ";
        cin >> arr[i];
    }

    out.open(file);
    if (out.is_open()) {
        for (int i = 0; i < len; i++) {
            out << arr[i] << endl;
        }
    }
    out.close();

    open(false, file);
}

// Функция-обработчик, задача "Знак"
int sign(float x) {
    int x;
    if (x > 0) x = 1;
    else if (x < 0) x = -1;
    else x = 0;
    return x;
}

void task17() {
    float x;
    cout << "Ввод x" << endl;
    cin >> x;
    cout << sign(x) << endl;
}

// Функции для вычисления площадей (задача "Геом. фигуры")
float rectangle(float x, float y) {
    return x * y;
}

float triangle(float x, float y, float z) {
    float p = (x + y + z) / 2;
    return sqrt(p * (p - x) * (p - y) * (p - z));
}

float circle(float r) {
    return M_PI * r * r;
}

void task18() {
    
}

void task19() {
    string line = "___________________________________________";
    string star = "********___________________________________";
    for (int i = 0; i < 13; i++) {
        if (i > 0 && i < 7) cout << star;
        else cout << line;
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    // 1 ДЗ
    /*
    task1();
    task2();
    task3();
    task4();
    task5();
    */

    // 2 ДЗ
    /*
    task6();
    task7();
    task8();
    task9();
    task10();
    */

    // 3 ДЗ
    /*
    task11();
    task12();
    task13();
    task14();
    task15();
    */

    // 4 ДЗ
    task16();
    task17();
    task19();


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

