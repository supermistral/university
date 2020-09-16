#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <Windows.h>
#include <map>
using namespace std;

void open(string file) {
    ifstream in(file);
    if (in.is_open()) {
        string line;

        while (getline(in, line)) {
            cout << line << endl;
        }
    }
    in.close();
}

void task16() {
    string file = "";  // Путь к файлу
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

    open(file);
}

// Функция-обработчик, задача "Знак"
int sign(float x) {
    int res;
    if (x > 0) res = 1;
    else if (x < 0) res = -1;
    else res = 0;
    return res;
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

void task20() {
    int startPos = 100;
    HDC window = GetDC(GetConsoleWindow());
    HPEN obj = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    SelectObject(window, obj);

    MoveToEx(window, 0, startPos, NULL);
    LineTo(window, startPos * 2, startPos);
    MoveToEx(window, startPos, 0, NULL);
    LineTo(window, startPos, startPos * 2);

    for (float x = -8.0; x <= 8.0; x += 0.01) {
        MoveToEx(window, 10 * x + startPos, -10 * sin(x) + startPos, NULL); //10 - scale
        LineTo(window, 10 * x + startPos, -10 * sin(x) + startPos);
    }
}

void task21() {
    map <string, int> dig = {
        {"I", 1}, {"V", 5}, {"X", 10}, {"IV", 4 }, {"IX", 9},
        {"L", 50}, {"XL", 40}, {"C", 100}, {"XC", 90}, {"D", 500}, 
        {"CD", 400}, {"M", 1000}, {"CM", 900}
    };
    string inputUser, temp = "", input;
    int len, i, result = 0;
    cout << "Ввод римского числа" << endl;
    cin >> input;
    len = input.length();
    //for (i = 0; i < len; i++) {
    //    input += inputUser[len - i - 1];
    //}
    i = len - 1;

    while (i >= 0) {
        if (i > 0) temp = string(1, input[i - 1]) + string(1, input[i]);
        if (i > 0 && dig[temp]) {
            result += dig[temp];
            i -= 2;
        }
        else {
            result += dig[string(1, input[i])];
            i -= 1;
        }
    }
    cout << result << endl;
}

void task22() {
    int m, i, c, s = 1, start = 1, end = 100;
    cout << "Ввод m, i, c" << endl;
    cin >> m >> i >> c;
    
    for (int i = start; i <= end; i++) {
        s = (m * s + i) % c;
        cout << s << endl;
    }
}

// Задать вопрос: цена / наценка 
void task23() {
    int prod[3][4] = {
        {5, 2, 0, 10},
        {3, 5, 2, 5},
        {20, 0, 0, 0}
    };
    float seller[4][2] = {
        {1.2, 0.5},
        {2.8, 0.4},
        {5, 1},
        {2, 1.5}
    };
    float res[3][2], temp;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 2; k++) {
            temp = 0;
            for (int j = 0; j < 4; j++) {
                temp += prod[i][j] * seller[j][k];
            };
            res[i][k] = temp;
        };
    };

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

void task24() {
    int oldBase, newBase;
    string userNum, newNum;
    cout << "Ввод числа, основания его системы счисления и основания системы счисления нового числа" << endl;
    cin >> userNum >> oldBase >> newBase;

    newNum = convert(convertToTen(userNum, oldBase), newBase);
    cout << newNum << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    task16();
    task17();
    //task(18);
    task19();
    task20();
    task21();
    task22();
    task23();
    task24();
    return 0;
}
