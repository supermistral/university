#include <iostream>
#include <fstream>
#include <string>

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
    float S, p = 0;
    int n;
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
    int len = line.length();
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
