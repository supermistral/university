#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {
    cout << x << " " << sin(x) << endl;
    return sin(x);
}

int main()
{
    const int n = 21, m = 61, half_n = n / 2, half_m = m / 2;
    double scale = M_PI / 14;
    char coords[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == half_m) {
                coords[i][j] = '|';
            }
            else if (i == half_n) {
                coords[i][j] = '-';
            }
            else {
                coords[i][j] = ' ';
            }
        }
    }

    int posy;
    for (int i = -half_m; i < half_m; i++) {
        posy = round(half_n - half_n * f(i * scale));
        coords[posy][i + half_m] = '*';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << coords[i][j];
        }
        cout << endl;
    }

    return 0;
}

