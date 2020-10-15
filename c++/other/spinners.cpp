#include <iostream>
using namespace std;

void task1() {
    long long a, b, c, n;
    cin >> a >> b >> c;

    for (n = 1; (a + b * n) <= c; n++);
    cout << n - 1 << "\n\n";
}

void task2() {
    long long m;
    float n;
    cin >> m;

    for (long long i = 0; m - 3 * i >= 0; i++) {
        n = (m - 3 * i) / 4.0;
        if (int(n) - n == 0) {
            cout << i << endl << int(n) << "\n\n";
            return;
        }
    }
    cout << 0 << endl << 0 << "\n\n";
}

void task3() {
    long n, m, sum = 0;
    cin >> n >> m;

    for (long i = 1; i <= n; i++) {
        for (long j = 1; j <= m; j++) {
            sum += (n - i + 1) * (m - j + 1);
        }
    }
    cout << sum << "\n\n";
}

bool check(bool* arr, int start, int len) {
    for (int i = start; i < start + len; i++) {
        if (!arr[i]) {
            return false;
        }
    }
    return true;
}

void task4() {
    int n, num;
    const int length = 54;
    cin >> n;

    bool arr[length];
    for (int i = 0; i < length; i++) {
        arr[i] = false;
    }

    for (int i = 0; i < n; i++) {
        cin >> num;
        arr[num - 1] = true;
    }

    int result = 0, temp = 0;
    for (int i = 0, j = length - 1; i < length / 6 * 4; i += 4, j -= 2) {
        if (check(arr, i, 4) && check(arr, j - 1, 2)) {
            temp += 1;
        }
        else {
            if (temp > result) {
                result = temp;
            }
            temp = 0;
        }
    }
    cout << result << "\n\n";
}

void task5() {
    long long n, k, n_previous, temp;
    cin >> n >> k;

    
}

int main()
{
    //task1();
    //task2();
    //task3();
    task4();

    return 0;
}
