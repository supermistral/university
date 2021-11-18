#include <iostream>


template <class Data>
struct AVLTree {

    struct Node {
        Data key;
        unsigned height;
        Node *left,
             *right;

        Node(Data key) :
            key(key), 
            left(nullptr),
            right(nullptr),
            height(1) {};
    };

    Node* root;

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteNode(root);
        root = nullptr;
    }

    void deleteNode(Node*& node) {
        if (node) {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    }

    // Получить высоту (для работы с нулевыми узлами)
    unsigned getHeight(Node *node) {
        return node ? node->height : 0;
    }

    // Установить высоту
    void setHeight(Node* node) {
        unsigned heightLeft = getHeight(node->left),
            heightRight = getHeight(node->right);

        node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
    }

    // Баланс фактор
    int balanceFactor(Node* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    // Малый поворот влево
    Node* rotateLeft(Node* nodeRotateCenter) {
        Node* nodeRotate = nodeRotateCenter->right;
        nodeRotateCenter->right = nodeRotate->left;
        nodeRotate->left = nodeRotateCenter;

        setHeight(nodeRotateCenter);
        setHeight(nodeRotate);
        
        return nodeRotate;
    }

    // Малый поворот вправо
    Node* rotateRight(Node* nodeRotateCenter) {
        Node* nodeRotate = nodeRotateCenter->left;
        nodeRotateCenter->right = nodeRotate->right;
        nodeRotate->left = nodeRotateCenter;

        setHeight(nodeRotateCenter);
        setHeight(nodeRotate);

        return nodeRotate;
    }

    // Балансировка
    Node* balance(Node* node) {
        setHeight(node);

        if (balanceFactor(node) == -2) {            // высота левого > правого
            if (balanceFactor(node->left) > 0) {        // большой поворот вправо
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (balanceFactor(node) == 2) {        // высота правого > левого
            if (balanceFactor(node->right) < 0) {       // большой поворот влево
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    // Вставка узла
    Node* insertNode(Node* node, Data key) {
        if (!node) {    // пустой узел
            return new Node(key);
        }

        if (key < node->key) {      // упорядочивание будущего узла по значению
            node->left = insertNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key);
        }
        else {
            return node;
        }

        return balance(node);   // рекурсивная балансировка после вставки
    }

    // Оболочка поверх insertNode
    void insert(Data key) {
        root = insertNode(root, key);
    }

    // Обратный обход (вывод узлов) 
    void reverseTraversalInternal(Node* node) {
        if (!node) {
            return;
        }

        reverseTraversalInternal(node->left);   // пройти все узлы
        reverseTraversalInternal(node->right);  // слева направо
        std::cout << node->key << " ";          // вывести значения снизу вверх
    }

    void reverseTraversal() {
        reverseTraversalInternal(root);
        std::cout << "\n";
    }

    // Симметричный обход
    void symmetricTraversalInternal(Node* node) {
        if (!node) {
            return;
        }

        symmetricTraversalInternal(node->left);     // пройти налево
        std::cout << node->key << " ";              // вывести значение
        symmetricTraversalInternal(node->right);    // пройти направо
    }

    void symmetricTraversal() {
        symmetricTraversalInternal(root);
        std::cout << "\n";
    }

    // Сумма значений листьев
    Data sumLeavesInternal(Node* node) {
        if (!node) {
            return 0;
        }

        if (!node->left && !node->right) {      // вернуть значение если это лист
            return node->key;
        }

        return sumLeavesInternal(node->left) + sumLeavesInternal(node->right);
    }

    // Обертка для суммы листьев
    Data sumLeaves() {
        return sumLeavesInternal(root);
    }

    // Среднее арифметическое всех узлов
    void avgNodesCounter(Node* node, Data& sum, int& amount) {
        if (node) {
            avgNodesCounter(node->left, sum, amount);
            sum += node->key;
            ++amount;
            avgNodesCounter(node->right, sum, amount);
        }
    }

    // Обертка для ср арифм узлов
    double avgNodes() {
        if (!root) {
            return 0;
        }

        Data sum = 0;
        int amount = 0;
        avgNodesCounter(root, sum, amount);

        return (double)sum / amount;
    }

    // Длина пути до заданного значения
    int pathLength(Data key) {
        Node* temp = root;
        int counter = 0;

        while (temp && temp->key != key) {
            if (key < temp->key) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
            ++counter;
        }

        return temp ? counter : -1;
    }

    void printInternal(Node* node, int space) {
        if (!node) {
            return;
        }

        space += 2;
        printInternal(node->right, space);

        for (int i = 2; i < space; ++i) {
            std::cout << " ";
        }
        std::cout << node->key << "\n";

        printInternal(node->left, space);
    }

    void print() {
        printInternal(root, 0);
    }
};


void run();

int main()
{
    run();
    return 0;
}


void run() {
    typedef double nodeData;

    std::string command;
    AVLTree<nodeData> tree;
    nodeData key;

    std::cout << "Work with AVL-tree\n"
        << "----------------\n"
        << "add <value>\n"
        << "print-rev\n"
        << "print-sym\n"
        << "sum-leaves\n"
        << "avg-nodes\n"
        << "path-len <key>\n"
        << "print\n"
        << "exit\n" 
        << "-----------------\n\n";

    while (1) {
        std::cin >> command;

        if (command == "add") {
            std::cin >> key;
            tree.insert(key);
        }
        else if (command == "print-rev") {
            tree.reverseTraversal();
        }
        else if (command == "print-sym") {
            tree.symmetricTraversal();
        }
        else if (command == "sum-leaves") {
            std::cout << "Sum = " << tree.sumLeaves() << "\n";
        }
        else if (command == "avg-nodes") {
            std::cout << "Avg = " << tree.avgNodes() << "\n";
        }
        else if (command == "path-len") {
            std::cin >> key;
            std::cout << "Length = " << tree.pathLength(key) << "\n";
        }
        else if (command == "print") {
            tree.print();
        }
        else if (command == "exit") {
            return;
        }
        else {
            std::cout << "No such command\n";
        }
        std::cout << "\n";
    }
}
