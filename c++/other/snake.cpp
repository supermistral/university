#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Points {
    int x, y;
};

bool operator== (Points a, Points b) {
    return (a.x == b.x && a.y == b.y);
}

char key_pressed();
void print(int a, int b);
int random(int a);
int key_handler(char a, int b = 0);
void move(vector<Points> snake, int a);
bool check(vector<Points> snake, int a);

int main()
{
    srand(time(NULL));
    //system("cls")
    const int height = 20, length = 50, start_posx = 1, start_posy = 1, snake_size = 4;
    char symbols[height][length];

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
        snake.push_back({i, start_posy});
    }
    
    int koefX = 0, koefY = 0;
    int posx, posy;
    char key;

    while (true) {
        system("cls");

        if (_kbhit()) {
            key = key_pressed();
            koefX = key_handler(key);
            koefY = key_handler(key, 1);
            //cout << koefX << endl << koefY;
        }
        posx = snake[snake_size - 1].x + koefX;
        posy = snake[snake_size - 1].y + koefY;
        if (posx >= length || posx <= 0 ||
            posy >= height || posy <= 0) {
            break;
        }

        //cout << snake[0].y << " " << snake[0].x;
        int tempX = snake[0].x, tempY = snake[0].y;
        //cout << posx << " " << posy << endl;
        //cout << tempX << " " << tempY << endl;
        symbols[tempY][tempX] = ' ';
        move(snake, snake_size);
        symbols[posy][posx] = '#';
        snake[snake_size - 1] = { posx, posy };

        if (!check(snake, snake_size)) {
            break;
        }
        // print
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                cout << symbols[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}

void move(vector<Points> snake, int size) {
    //int size = snake.size() - 1;
    int posx, posy;
    for (int i = 0; i < size - 1; i++) {
        posx = snake[i + 1].x;
        posy = snake[i + 1].y;
        snake[i] = { posx, posy };
        cout << snake[i].x << " " << snake[i].y << endl;
    }
}

bool check(vector<Points> snake, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (snake[size - 1] == snake[i]) {
            return false;
        }
    }
    return true;
}

int random(int n) {
    return rand() % n;
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


void print(int n, int m) {
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0 || j == m - 1) {
                cout << "#";
            }
            else if (i == 0 || i == n - 1) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }*/

}
