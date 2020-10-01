#include <iostream>
#include <math.h>
using namespace std;

double f(double x) {
    return sin(x);
}

int main()
{
    const int n = 27, m = 101, half_n = n / 2, half_m = m / 2;
    double scale = 7.0;
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
        posy = round(half_n - half_n * f(i / scale));
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
