#include <iostream>
#include <ctime>

const int ARR_SIZE = 10;

struct Node {
    int data;
    Node* next;

    Node(int data, Node* next)
        : data(data), next(next) {};
};

void insert(Node*&, int);
void pushBack(Node*&, int);
Node* getNewList(int);
void printList(Node*);
void deleteList(Node*&);

Node** createArray(Node*);
Node* createListFromArray(Node**);
void pushBackNode(Node*&, Node*);

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int length;
    std::cout << "List size = "; std::cin >> length;
    
    Node* head = getNewList(length);
    std::cout << "\nInitial ";
    printList(head);

    Node** arr = createArray(head);
    std::cout << "\nContents of array A\n";
    for (int i = 0; i < ARR_SIZE; ++i) {
        std::cout << i << " ";
        printList(arr[i]);
    }
    std::cout << "\n";

    Node* newHead = createListFromArray(arr);
    std::cout << "Resulting ";
    printList(newHead);

    deleteList(head);
    deleteList(newHead);
    delete[] arr;
    
    return 0;
}


void insert(Node*& head, int data) {
    Node* newNode = new Node(data, head);
    head = newNode;
}

void pushBack(Node*& head, int data) {
    if (!head) {
        insert(head, data);
        return;
    }

    Node* newNode = new Node(data, nullptr);
    Node* lastNode = head;

    while (lastNode->next)
        lastNode = lastNode->next;
    lastNode->next = newNode;
}

Node* getNewList(int length) {
    Node* head = nullptr;
    for (int i = 0; i < length; ++i)
        insert(head, rand() % 100);
    return head;
}

void printList(Node* head) {
    std::cout << "List: ";
    if (!head) {
        std::cout << "empty\n";
        return;
    }
    std::cout << head->data;
    for (Node* temp = head->next; temp; temp = temp->next)
        std::cout << " -> " << temp->data;
    std::cout << "\n";
}

Node** createArray(Node* headMainList) {
    Node** arr = new Node * [ARR_SIZE] { nullptr };
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (
            Node* tempHead = headMainList;
            tempHead;
            tempHead = tempHead->next
        ) {
            if (tempHead->data / 10 == i)
                pushBack(arr[i], tempHead->data);
        }
    }
    return arr;
}

void deleteList(Node*& head) {
    Node* next;
    for (Node* current = head; current; current = next) {
        next = current->next;
        delete current;
    }
    head = nullptr;
}

void pushBackNode(Node*& head, Node* node) {
    if (!head) {
        head = node;
        return;
    }

    Node* lastNode = head;
    while (lastNode->next)
        lastNode = lastNode->next;
    lastNode->next = node;
}

Node* createListFromArray(Node** arr) {
    Node* head = nullptr;
    for (int i = 0; i < ARR_SIZE; ++i)
        pushBackNode(head, arr[i]);
    return head;
}

//Node* createListFromArray(Node** arr) {
//    Node* head = nullptr;
//    for (int i = 0; i < ARR_SIZE; ++i)
//        for (Node* current = arr[i]; current; current = current->next)
//            pushBack(head, current->data);
//    return head;
//}
