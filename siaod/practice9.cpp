#include <iostream>
#include <cmath>

const int ARR_SIZE = 6;

void fillArray(int*);
int funcByPattern(int*, int);
int funcByPatternIter(int*, int);

class List {
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(Node* next, Node* prev, int data)
            : next(next), prev(prev), data(data) {};
    };
    Node* head = nullptr;

public:
    void push(int);
    void removeNode(Node*&);
    void removeList();
    void print();

    List();
    ~List();
};


int main()
{
    //int arr[ARR_SIZE];
    //fillArray(arr);

    // решение уравнения x(x+1)/2 = arr_size
    // x - порядковый номер скобки с суммой
    //const int call_num = (sqrt(1 + 8 * ARR_SIZE) - 1) / 2;
    //std::cout << funcByPattern(arr, call_num);

    List list;
    list.print();
    std::cout << "\nremoving...";
    list.removeList();
    list.print();
}


void fillArray(int* arr) {
    for (int i = 0; i < ARR_SIZE; ++i)
        arr[i] = i + 1;
}

int funcByPattern(int* arr, int n) {
    if (n < 1)
        return 1;

    int sum = 0, k = n * (n - 1) / 2;
    for (int i = 0; i < n; ++i)
        sum += arr[i + k];

    return sum * funcByPattern(arr, n - 1);
}

int funcByPatternIter(int* arr, int n) {
    int res = 1;

    for (int i = 0, k = 1, sum = 0; i < n; ++k) {
        sum = 0;
        for (int j = 0; j < k; ++j, ++i)
            sum += arr[i];
        res *= sum;
    }

    return res;
}

List::List() {
    int length, data;
    std::cout << "Length = "; std::cin >> length;
    for (int i = 0; i < length; ++i) {
        std::cin >> data;
        this->push(data);
    }
}

void List::push(int data) {
    Node* newNode = new Node(head, nullptr, data);
    if (head)
        head->prev = newNode;
    head = newNode;
}

void List::removeNode(Node*& node) {
    if (node) {
        removeNode(node->next);
        delete node;
    }
}

void List::removeList() {
    this->removeNode(head);
    head = nullptr;
}

void List::print() {
    if (!head) {
        std::cout << "\nempty";
        return;
    }

    std::cout << "\n" << head->data;
    for (Node* temp = head->next; temp; temp = temp->next)
        std::cout << " <-> " << temp->data;
}

List::~List() {
    this->removeList();
}
