// stack.cpp
#include "stack.h"

Stack::Node::Node(Node* next, int data)
    : next(next), data(data) {
};

void Stack::push(int data) {
    Node* newNode = new Node(head, data);
    head = newNode;
};

int Stack::pop() {
    int dataToReturn = head->data;
    Node* temp = head->next;
    delete head;
    head = temp;

    return dataToReturn;
};

bool Stack::isEmpty() {
    return head ? false : true;
};

Stack::~Stack() {
    while (head)
        this->pop();
}
