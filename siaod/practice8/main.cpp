#include <iostream>
#include "stack.h"
#include <string>
#include <algorithm>

int calculatePost(std::string);
int calculatePre(std::string);
std::string sumFromStrings(std::string, std::string);

int main()
{
    //std::string expression;
    //std::getline(std::cin, expression);
    //std::cout << calculatePre(expression);

    std::string num1, num2;
    std::cin >> num1 >> num2;
    std::cout << sumFromStrings(num1, num2);
}

int calculatePost(std::string expression) {
    Stack stack;
    for (size_t ind = 0; ind < expression.size(); ++ind) {
        if (expression[ind] >= '0' && expression[ind] <= '9') {
            size_t indEnd = expression.find(" ", ind);
            if (indEnd == std::string::npos)
                indEnd = expression.size();
            stack.push(std::stoi(expression.substr(ind, indEnd - ind)));
            ind = indEnd;
        }
        else {
            switch (expression[ind]) {
            case '+':
                stack.push(stack.pop() + stack.pop());
                break;
            case '-':
                stack.push(-stack.pop() + stack.pop());
                break;
            case '*':
                stack.push(stack.pop() * stack.pop());
                break;
            case '/':
                stack.push(1.0 / stack.pop() * stack.pop());
                break;
            }
        }
    }
    return stack.pop();
}

int calculatePre(std::string expression) {
    std::reverse(expression.begin(), expression.end());
    Stack stack;
    for (size_t ind = 0; ind < expression.size(); ++ind) {
        if (expression[ind] >= '0' && expression[ind] <= '9') {
            size_t indEnd = expression.find(" ", ind);
            if (indEnd == std::string::npos)
                indEnd = expression.size();
            std::reverse(expression.begin() + ind, expression.begin() + indEnd);
            stack.push(std::stoi(expression.substr(ind, indEnd - ind)));
            ind = indEnd;
        }
        else {
            switch (expression[ind]) {
            case '+':
                stack.push(stack.pop() + stack.pop());
                break;
            case '-':
                stack.push(stack.pop() - stack.pop());
                break;
            case '*':
                stack.push(stack.pop() * stack.pop());
                break;
            case '/':
                stack.push(stack.pop() / stack.pop());
                break;
            }
        }
    }
    return stack.pop();
}

std::string sumFromStrings(std::string num1, std::string num2) {
    if (num1.size() > num2.size())
        num1.swap(num2);
    std::string result(num2.size(), ' ');
    int         nextDischarge = 0, 
                currentNum = 0,
                counter = num2.size() - 1,
                diff = num2.size() - num1.size();

    for (size_t ind = num1.size(); ind-- > 0; ) {
        currentNum = num1[ind] - '0' + num2[ind+diff] - '0' + nextDischarge;
        nextDischarge = currentNum / 10;
        result[counter--] = currentNum % 10 + '0';
    }
    
    for (size_t ind = diff; ind-- > 0; ) {
        currentNum = num2[ind] - '0' + nextDischarge;
        nextDischarge = currentNum / 10;
        result[counter--] = currentNum % 10 + '0';
    }

    if (nextDischarge)
        result.insert(result.begin(), '1');
    
    return result;
}
