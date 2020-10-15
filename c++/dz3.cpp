#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Обработчик для задач Заем и Ссуда
// функция с возвратом m
double task1_helper(float S, float p, int n) {
    float r = p / 100;
    return S * r * pow(1 + r, n) / (12 * (pow(1 + r, n) - 1));
}

void task1() {
    float S, p;
    int n;
    cout << "Ввод S, p, n" << endl;
    cin >> S >> p >> n;
    if (S <= 0 || p <= 0 || n <= 0) {
        cout << "Параметры должны быть положительными" << endl;
        return;
    }

    cout << "m = " << task1_helper(S, p, n) << endl;
}

// Перебор целых значений процентов от 0 до 100
void task2() {
    float S;
    int n, p;
    double m;
    cout << "Ввод S, m, n" << endl;
    cin >> S >> m >> n;
    if (S <= 0 || m <= 0 || n <= 0) {
        cout << "Параметры должны быть положительными" << endl;
        return;
    }

    int diff = -1;
    for (int i = 0; i <= 100; i++) {
        if ((fabs(task1_helper(S, i, n) - m) < diff) || (diff < 0)) {
            p = i;
            diff = fabs(task1_helper(S, i, n) - m);
        }
    }

    if (diff <= 0.1) {
        cout << "p = " << p << endl;
        return;
    }
    cout << "При введенных данных слишком большая погрешность p" << endl;
}

// Задачи "Копирование файла" и "фильтр" - одно и то же
// Обработчик для задачи "фильтр" - проверка на числовой тип строки
void task4_helper(string line) {
    int len = line.size();
    for (int i = 0; i < len; i++) {
        if (isdigit(line[i]) || line[i] == ' ') {
            cout << line[i];
        }
    }
}

// Открытие файла и вывод содержимого, требуется в рамках обоих задач
// Аргумент для удобства - чтобы не повторять код в другой задаче и
// вызывать функцию выше, когда нужно
void open(bool cond = false, string file = "C:\\Users\\IVC1-5\\Desktop\\test.txt") {  // Путь к файлу
    ifstream in(file);
    if (in.is_open()) {
        cout << "Содержимое файла:" << endl;
        string line;

        while (!in.eof()) {
            getline(in, line);
            if (cond) {
                task4_helper(line);
            }
            else {
                cout << line;
            }
            cout << endl;
        }
    }
    in.close();
}

void task3() {
    string file = "C:\\Users\\IVC1-5\\Desktop\\test.txt";
    ofstream out(file);

    if (out.is_open()) {
        cout << "Заполните файл содержимым. Конец заполнения - '0'" << endl;
        string line;
        do {
            getline(cin, line);
            out << line << endl;
        } while (line != "0");
    }
    out.close();
    cout << endl;

    open();
}

// Вызов открытия файла - предыдущей задачи с аргументом для вызова хелпера
void task4() {
    open(true);
}

// Можно ввести сколь угодно много символов - используются первые 30
// сортировка пузырьком
void task5() {
    const int length = 30;
    string userLine;
    cout << "Ввод строки" << endl;
    cin >> userLine;

    if (userLine.size() < 30) {
        cout << userLine.size() << endl;
        cout << "Строка должна содержать не менее 30 символов" << endl;
        return;
    }
    userLine.resize(length);
    cout << "Используемая строка - " << userLine << endl;

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

    //task1();
    //task2();
    task3();
    //task4();
    //task5();
    return 0;
}
