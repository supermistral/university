#include <iostream>
#include <map>
using namespace std;

void roman() {
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

int main()
{
    setlocale(LC_ALL, "rus");
    roman();

    return 0;
}
