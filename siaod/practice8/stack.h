// stack.h
#pragma once

class Stack {
    struct Node {
        int data;
        Node* next = nullptr;
        Node(Node*, int);
    };
    Node* head = nullptr;

public:
    void push(int);
    int pop();
    bool isEmpty();

    ~Stack();
};
