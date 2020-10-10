#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <Windows.h>
#include <map>
using namespace std;

float open(string file) {
    float sum = 0;
    ifstream in(file);

    if (in.is_open()) {
        string line;

        while (getline(in, line)) {
            cout << line << endl;
            sum += stof(line);
        }
    }
    in.close();
    return sum;
}

void task1() {
    string file = "";  // Путь к файлу
    const int len = 10;
    float arr[len];
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

    cout << "Сумма = " << open(file) << endl;;
}

// Функция-обработчик, задача "Знак"
int sign(float x) {
    int res;
    if (x > 0) res = 1;
    else if (x < 0) res = -1;
    else res = 0;
    return res;
}

void task2() {
    float x;
    cout << "Введите x -> "; cin >> x;
    cout << sign(x) << endl;
}

// Функции для вычисления площадей (задача "Геом. фигуры")
double rectangle(float x, float y) {
    return x * y;
}

double triangle(float x, float y, float z) {
    float p = (x + y + z) / 2;
    return sqrt(p * (p - x) * (p - y) * (p - z));
}

double circle(float r) {
    return M_PI * r * r;
}

void task3() {
    float x, y, z;
    cout << "Ввод сторон прямоугольника" << endl; cin >> x >> y;
    cout << rectangle(x, y) << endl;
    cout << "Ввод сторон треугольника" << endl; cin >> x >> y >> z;
    cout << triangle(x, y, z) << endl;
    cout << "Ввод радиуса круга" << endl; cin >> x;
    cout << circle(x) << endl;
}

void task4() {
    string line = "___________________________________________";
    string star = "********___________________________________";
    for (int i = 0; i < 13; i++) {
        if (i > 0 && i < 7) cout << star;
        else cout << line;
        cout << endl;
    }
}

void task5() {
    int startPos = 100, scaleX = 10, scaleY = -20;
    HDC window = GetDC(GetConsoleWindow());
    HPEN obj = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    SelectObject(window, obj);

    MoveToEx(window, 0, startPos, NULL);
    LineTo(window, startPos * 2, startPos);
    MoveToEx(window, startPos, 0, NULL);
    LineTo(window, startPos, startPos * 2);

    for (float x = -10; x <= 10; x += 0.01f) {
        MoveToEx(window, x * scaleX + startPos, sin(x) * scaleY + startPos, NULL);
        LineTo(window, x * scaleX + startPos, sin(x) * scaleY + startPos);
    }
}

void task6() {
    map <char, int> dig = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500},
        {'M', 1000}
    };
    string input;
    int result = 0, counter = 1;
    cout << "Ввод римского числа -> "; cin >> input;
    char tempSym = input[0];
    int len = input.size();

    for (int i = 0; i < len - 1; i++) {
        //Блок проверки на более чем 3 одинаковых цифры подряд
        if (input[i + 1] == tempSym) {
            counter++;
            if (counter > 3) {
                cout << "Неверная запись римского числа" << endl;
                return;
            }
        }
        else {
            //Чек на вхождение символа в словарь
            if (dig.find(input[i]) == dig.end()) {
                cout << "Неверная запись римского числа" << endl;
                return;
            }
            tempSym = input[i];
            counter = 1;
        }

        if (dig[input[i]] < dig[input[i + 1]]) {
            result -= dig[input[i]];
        }
        else {
            result += dig[input[i]];
        }
    }
    result += dig[input[len - 1]];
    cout << result << endl;
}

double task7_helper(int m, int i, int c, int s) {
    return (m * s + i) % c;
}

void task7() {
    int s = 0, start = 0, end = 10;
    
    cout << "1 вариант:" << endl;
    for (int i = start; i < end; i++) {
        s = task7_helper(37, 3, 64, s);
        cout << s << endl;
    }
    
    s = 0;
    cout << "2 вариант:" << endl;
    for (int i = start; i < end; i++) {
        s = task7_helper(25173, 13849, 65537, s);
        cout << s << endl;
    }
}

void task8() {
    const int n = 3, m1 = 4, m2 = 2;
    double prod[n][m1] = {
        {5, 2, 0, 10},
        {3, 5, 2, 5},
        {20, 0, 0, 0}
    };
    double seller[m1][m2] = {
        {1.2, 0.5},
        {2.8, 0.4},
        {5, 1},
        {2, 1.5}
    };
    double res[n][m2], sum1 = 0, sum2 = 0;

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m2; k++) {
            res[i][k] = 0;
            for (int j = 0; j < m1; j++) {
                res[i][k] += prod[i][j] * seller[j][k];
            }
        }
    }

    // 1
    double max = res[0][0], min = res[0][0];
    int prod1 = 1, prod2 = 1;
    for (int i = 1; i < n; i++) {
        if (max < res[i][0]) {
            max = res[i][0];
            prod1 = i + 1;
        }
        if (min > res[i][0]) {
            min = res[i][0];
            prod2 = i + 1;
        }
        sum1 += res[i][0];
    }
    cout << "Наибольшую выручку имеет " << prod1 << " | Наименьшую вырочку имеет " << prod2 << endl;

    // 2
    max = res[0][1], min = res[0][1];
    prod1 = 1, prod2 = 1;
    for (int i = 1; i < n; i++) {
        if (max < res[i][1]) {
            max = res[i][1];
            prod1 = i + 1;
        }
        if (min > res[i][1]) {
            min = res[i][1];
            prod2 = i + 1;
        }
        sum2 += res[i][1];
    }
    cout << "Наибольшие комиссионные имеет " << prod1 << " | Наименьшие комиссионные имеет " << prod2 << endl;

    // 3
    cout << "Всего выручили " << sum1 << endl;

    // 4
    cout << "Всего комиссионных " << sum2 << endl;

    // 5
    cout << "Через руки продавцов прошли " << sum1 + sum2 << endl;
}

// Перевод в целевую
string convert(int num, int base) {
    int currentNum, scale1 = 55, scale2 = 48;
    string newNum = "";

    while (num > 0) {
        currentNum = num % base;
        if (currentNum > 9) {
            newNum = char(currentNum + scale1) + newNum;
        }
        else {
            newNum = char(currentNum + scale2) + newNum;
        }
        num /= base;
    }
    return newNum;
}

// Перевод в десятичную
int convertToTen(string num, int base) {
    int currentNum, newNum = 0, scale1 = 55, scale2 = 48, dig = 1;

    while (!num.empty()) {
        int lastSym = num[num.size() - 1];
        if (lastSym >= scale1 + 10) {
            currentNum = lastSym - scale1;
        }
        else {
            currentNum = lastSym - scale2;
        }
        newNum += currentNum * dig;
        dig *= base;
        num.erase(num.size() - 1);
    }
    return newNum;
}

void task9() {
    int oldBase, newBase;
    string userNum, newNum;
    cout << "Ввод числа, основания его системы счисления и основания системы счисления нового числа" << endl;
    cin >> userNum >> oldBase >> newBase;

    newNum = convert(convertToTen(userNum, oldBase), newBase);
    cout << newNum << endl;
}

boolean handler(char x) {
    switch (x)
    {
    case '1':
        task1();
        break;
    case '2':
        task2();
        break;
    case '3':
        task3();
        break;
    case '4':
        task4();
        break;
    case '5':
        task5();
        break;
    case '6':
        task6();
        break;
    case '7':
        task7();
        break;
    case '8':
        task8();
        break;
    case '9':
        task9();
        break;
    default:
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "rus");
    
    boolean condition = true;
    char input;
    while (condition) {
        cout << "№ Задания -> "; cin >> input;
        condition = handler(input);
        cout << endl;
    }

    return 0;
}
