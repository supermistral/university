#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace std;

struct Points {
    int x, y;
};

bool operator== (Points a, Points b) {
    return (a.x == b.x && a.y == b.y);
}
//
void setpos(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char key_pressed();
int random(int a, int b = 0);
int key_handler(char a, int b = 0);
void move(vector<Points>& snake, int a);
bool check(vector<Points>& snake, int a);
Points food(int a, int b);
bool check_food(vector<Points>& snake, int a, Points b);
int set_speed();
bool game(int a, int b, int c, int d, int e);

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    //system("cls")
    const int height = 26, length = 52, start_posx = 1, start_posy = 1;
    int snake_size = 4;

    bool gameCondition = true;
    while (gameCondition) {
        gameCondition = game(height, length, start_posx, start_posy, snake_size);
    }
    return 0;
}

bool game(int height, int length, int start_posx, int start_posy, int snake_size) {
    char** symbols = new char*[height];
    for (int i = 0; i < height; i++) {
        symbols[i] = new char[length];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            if (j == 0 || j == length - 1 || i == 0 || i == height - 1) {
                symbols[i][j] = '+';
            }
            else {
                symbols[i][j] = ' ';
            }
        }
    }
    // snake
    vector<Points> snake;
    //int head_posx = start_posx + snake_size - 1, head_posy = start_posy;
    //int end_posx = start_posx, end_posy = start_posy;
    for (int i = start_posx; i < start_posx + snake_size; i++) {
        symbols[start_posy][i] = '#';
        snake.push_back({ i, start_posy });
    }

    int koefX = 1, koefY = 0;
    int posx, posy;
    char key;
    Points posFood = food(length, height);
    symbols[posFood.y][posFood.x] = '*';

    int speed = set_speed();
    long score = 0;
    system("cls");

    while (true) {
        setpos(0, 0);
        Sleep(speed);

        if (_kbhit()) {
            key = key_pressed();
            koefX = key_handler(key);
            koefY = key_handler(key, 1);
            //cout << koefX << endl << koefY;
        }
        posx = snake[snake_size - 1].x + koefX;
        posy = snake[snake_size - 1].y + koefY;
        // Выход за границы 
        if (posx >= length - 1 || posx <= 0 ||
            posy >= height - 1 || posy <= 0) {
            //break;
            if (posx >= length - 1) {
                posx = 1;
            }
            else if (posx <= 0) {
                posx = length - 2;
            }
            else if (posy >= height - 1) {
                posy = 1;
            }
            else if (posy <= 0) {
                posy = height - 2;
            }
        }


        symbols[snake[0].y][snake[0].x] = ' ';
        move(snake, snake_size);
        symbols[posy][posx] = '#';
        snake[snake_size - 1] = { posx, posy };

        if (!check(snake, snake_size)) {
            break;
        }

        if (check_food(snake, snake_size, posFood)) {
            auto iter = snake.cbegin();
            snake.insert(iter, snake[0]);
            ++snake_size;
            ++score;
            posFood = food(length, height);
            symbols[posFood.y][posFood.x] = '*';
        }
        // print
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                cout << symbols[i][j];
            }
            cout << "\n";
        }
    }
    for (int i = 0; i < height; i++) {
        delete[] symbols[i];
    }
    delete[] symbols;

    char k = 'q';
    system("cls");
    cout << "Ваш счет >> " << score << "\n\n";
    cout << "Для выхода нажмите q, в случае продолжения нажмите любую другую клавишу" << "\n\n";
    k = key_pressed();
    return (k != 'q');
}

void move(vector<Points>& snake, int size) {
    int posx, posy;
    for (int i = 0; i < size - 1; i++) {
        snake[i] = snake[i + 1];
    }
    /*for (int i = 0; i < size; i++) {
        cout << snake[i].x << " " << snake[i].y << endl;
    }*/
}

Points food(int l, int h) {
    int x = random(l - 2, 1);
    int y = random(h - 2, 1);
    return { x, y };
}

bool check_food(vector<Points>& snake, int size, Points food) {
    return (snake[size - 1] == food);
}

bool check(vector<Points>& snake, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (snake[size - 1] == snake[i]) {
            return false;
        }
    }
    return true;
}

int set_speed() {
    double x;
    cout << "Установка скорости 1 - 1000 -> "; cin >> x;
    cout << "\r";
    if (int(x) - x == 0 && x >= 1 && x <= 1000) {
        return x;
    }
    else {
        return set_speed();
    }
}

int random(int n, int mod) {
    return mod + rand() % n;
}

// 1 - y, 0 - x
int key_handler(char key, int mod) {
    int x = 0, y = 0;
    switch (key) {
        case 'w':
            y = -1;
            break;
        case 'a':
            x = -1;
            break;
        case 's':
            y = 1;
            break;
        case 'd':
            x = 1;
        default:
            break;
    }
    if (mod) return y;
    return x;
}

char key_pressed() {
    // w = 
    char key = _getch();
    return key;
}
