#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Обработчик для задач Заем и Ссуда
// функция с возвратом m
double task11_helper(float S, float p, int n) {
    float r = p / 100;
    double temp = pow(1 + r, n);
    return S * r * temp / (12 * (temp - 1));
}

void task11() {
    float S, p;
    int n;
    cout << "Ввод S, p, n" << endl;
    cin >> S >> p >> n;
    cout << task11_helper(S, p, n) << endl;
}

// Перебор целых значений процентов от 1 до 100
void task12() {
    float S;
    int n, p = 0;
    double m;
    cout << "Ввод S, m, n" << endl;
    cin >> S >> m >> n;

    for (int i = 1; i <= 100; i++) {
        if (task11_helper(S, i, n) == m) {
            p = i;
            break;
        }
    }

    if (p) cout << p;
    else cout << "Не удалось определить целое p";
    cout << endl;
}

// Задачи "Копирование файла" и "фильтр" - одно и то же
// Обработчик для задачи "фильтр" - проверка на числовой тип строки
void task14_helper(string line) {
    int dig;
    int len = line.size();
    for (int i = 0; i < len; i++) {
        dig = line[i];
        if (dig) cout << dig;
    }
}

// Открытие файла и вывод содержимого, требуется в рамках обоих задач
// Аргумент для удобства - чтобы не повторять код в другой задаче и
// вызывать функцию выше, когда нужно
void open(bool cond = false, string file = "") {  // Путь к файлу
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
    string userLine;
    cout << "Ввод строки" << endl;
    cin >> userLine;
    userLine.resize(length);
    cout << "Ваша строка - " << userLine << endl;

    char k;
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (userLine[j] > userLine[j + 1]) {
                k = userLine[j];
                userLine[j] = userLine[j + 1];
                userLine[j + 1] = k;
            }
        }
    }
    cout << userLine << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    task11();
    task12();
    task13();
    task14();
    task15();
    return 0;
}
