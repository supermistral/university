#include <iostream>
#include <string>
#include <fstream>
#define SHIFT_LEN 4
using namespace std;

enum MODIFICATOR {
    F_OPEN, F_WRITE
};

bool handler(string);
void open(string);
void write(string);
string shift(string, MODIFICATOR);

int main()
{
    setlocale(LC_ALL, "rus");
    string file = "C:\\Users\\IVC1-5\\Desktop\\test.txt";
    bool running = true;
    while (running) {
        running = handler(file);
        cout << "\n";
    }

    return 0;
}

bool handler(string file) {
    char input;
    cout << "Режим работы: 'o' - открытие, 'w' - запись -> ";
    cin >> input;
    switch (input) {
    case 'o':
        open(file);
        break;
    case 'w':
        write(file);
        break;
    default:
        cout << "Выход..." << "\n";
        return false;
    }
    return true;
}

void write(string file) {
    ofstream out(file);

    if (out.is_open()) {
        cout << "Заполните файл содержимым. Конец заполнения - '0'" << "\n";
        string line;
        do {
            getline(cin, line);
            if (line == "0") {
                break;
            }
            out << shift(line, F_WRITE) << "\n";
        } while (line != "0");
        out.close();
    }
    else {
        cout << "Ошибка открытия файла" << "\n";
    }
}

void open(string file) {
    ifstream in(file);
    if (in.is_open()) {
        cout << "Содержимое файла:" << endl;

        string line;
        while (!in.eof()) {
            getline(in, line);
            cout << shift(line, F_OPEN) << "\n";
        }
        in.close();
    }
    else {
        cout << "Ошибка открытия файла" << "\n";
    }
}

string shift(string line, MODIFICATOR mod) {
    int k;
    switch (mod) {
    case F_OPEN:
        k = -1;
        break;
    case F_WRITE:
        k = 1;
        break;
    }
    for (size_t i = 0; i < line.size(); i++) {
        line[i] = char(line[i] + SHIFT_LEN * k);
    }
    return line;
}
