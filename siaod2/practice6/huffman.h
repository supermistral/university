#pragma once
#include <string>
#include <map>
#include <queue>


class Huffman {
    struct node {       // узел дерева
        node* left,
            *right;
        std::string bits,   // код узла
            value;          // значение для DOT
        char symbol;        // символ
        int amount;         // кол-во вхождений символа

        node(char symbol, int amount = 0, node* left = nullptr, node* right = nullptr)
            : symbol(symbol), amount(amount), value(std::string(1, symbol)), 
              left(left), right(right) {};
    };

    struct nodeComparator {     // компаратор для приоритетной очереди
        bool operator() (const node& a, const node& b) const {
            return a.amount > b.amount;     // чем меньше вхождений, тем раньше выйдет из очереди
        }
    };

    struct symbolNode {     // таблица символов
        int amount;
        std::string bits;
    };

    node* root;
    std::string text;
    std::map<char, symbolNode> bitsMap;

    // заполнение таблицы символов по тексту
    void setBitsMap() {
        for (int i = 0; i < text.size(); ++i) {
            if (bitsMap.find(text[i]) == bitsMap.end()) {
                bitsMap.insert({ text[i], { 0, "" } });
            }
            bitsMap[text[i]].amount += 1;
        }
    }

    // заполнение таблицы символов по таблице вхождений
    void setBitsMap(std::map<char, int> amounts) {
        for (const auto& p : amounts) {
            bitsMap.insert({ p.first, { p.second, "" } });
        }
    }

    // начальная инициализация по тексту
    void setInitialState(std::string text) {
        clear();
        this->text = text;
        setBitsMap();
    }

    // начальная инициализация по тексту и вхождениям символов
    void setInitialState(std::string text, std::map<char, int> amounts) {
        clear();
        this->text = text;
        setBitsMap(amounts);
    }

    // проход по дереву и присвоение кодов листам
    void setBits(node *n, std::string bits) {
        if (!n)
            return;

        if (!(n->left) && !(n->right)) {
            bitsMap[n->symbol].bits = bits;
        }
        else {
            setBits(n->left, bits + "1");
            setBits(n->right, bits + "0");
        }
    }

    // построить дерево Хаффмана
    void buildTree() {
        std::priority_queue<node, std::vector<node>, nodeComparator> queue; // приоритетная очередь

        for (const auto& p : bitsMap) {
            queue.push(node(p.first, p.second.amount ));     // заполнить очередь узлами с символами
        }

        while (queue.size() > 1) {
            node *n1 = new node(queue.top());       // взять 2 первых узла (с наименьшими вхождениями)
            queue.pop();
            node *n2 = new node(queue.top());
            queue.pop();

            node* newNode = new node('\0', n1->amount + n2->amount, n2, n1);    // новый узел -
            newNode->value = n2->value + n1->value;                             // родитель для 2ух
           
            queue.push(*newNode);
            
        }
         
        root = new node(queue.top());       // корень - последний узел в очереди
    }

    // проверка на существование битовой последов-ти
    bool containsBits(std::string bits) {
        for (const auto& p : bitsMap) {
            if (p.second.bits == bits) {
                return true;
            }
        }
        return false;
    }

    // получение символа по битовому коду
    char getSymbol(std::string bits) {
        for (const auto& p : bitsMap) {
            if (p.second.bits == bits) {
                return p.first;
            }
        }
        return '\0';
    }

    // вывод дерева Хаффмана в ДОТ-нотации
    void printDOTRecursive(node* n) {
        if (!n)
            return;

        if (n->left) {
            std::cout << "\n\"" << n->value << "(" << n->amount << ")\" -> \""
                << n->left->value << "(" << n->left->amount << ")\";";
        }
        if (n->right) {
            std::cout << "\n\"" << n->value << "(" << n->amount << ")\" -> \""
                << n->right->value << "(" << n->right->amount << ")\";";
        }

        printDOTRecursive(n->left);
        printDOTRecursive(n->right);
    }

    void deleteNodeRecursive(node* n) {
        if (!n)
            return;
        deleteNodeRecursive(n->left);
        deleteNodeRecursive(n->right);
        delete n;
    }

public:
    // кодирование
    void encode() {
        buildTree();            // построить дерево Хаффмана по таблице вхождений
        setBits(root, "");      // установить битовый код для листьев дерева
    }

    void encode(std::string text) {
        setInitialState(text);
        encode();
    }

    // получение сжатого текста
    std::string getEncodedText() {
        std::string result;

        for (char sym : text) {
            result += bitsMap[sym].bits;
        }

        return result;
    }

    // дотанц
    void printDOT() {
        std::cout << "\nDigraph G {";
        printDOTRecursive(root);
        std::cout << "\n}";
    }

    // вывод информации о сжатии
    void printEncodedString() {
        for (const auto& p : bitsMap) {
            std::cout << "\n" << p.first << " " << p.second.bits;
        }

        std::string result = getEncodedText();

        std::cout << "\nEncoded message: " << result
            << "\nBits: " << result.size()
            << "\nSource text size: " << text.size() * 8;
    }

    ~Huffman() {
        deleteNodeRecursive(root);
    }

    // чтение файла и иницализация прочитанным текстом
    bool readFile(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            file.close();
            return false;
        }

        std::string line, text;
        std::getline(file, line);

        while (std::getline(file, line)) {
            text += " " + line;
        }

        file.close();
        setInitialState(text);

        return true;
    }

    // чтение файла с сжатым текстом
    bool readEncodedFile(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            file.close();
            return false;
        }

        std::string line, text;
        std::map<char, int> amounts;

        std::getline(file, text);

        while (std::getline(file, line)) {
            amounts.insert({ line[0], std::stoi(line.substr(2)) });
        }

        setInitialState(text, amounts);
        file.close();

        return true;
    }

    // запись в файл сжатого текста и таблицы вхождений
    bool writeFile(std::string filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            file.close();
            return false;
        }

        file << getEncodedText();

        for (const auto& p : bitsMap) {
            file << "\n" << p.first << " " << p.second.amount;
        }

        return true;
    }

    void clear() {
        deleteNodeRecursive(root);
        bitsMap.clear();
        text.clear();
    }

    // декодирование
    std::string decode() {
        buildTree();        // построить дерево Хаффмана по таблице вхождений
        setBits(root, "");  // установить битовый код для листьев дерева

        for (const auto& p : bitsMap) {
            std::cout << "\n" << p.first << " " << p.second.bits;
        }

        int ind = 0, 
            size = text.size();
        std::string currentBits = "",
            result = "";

        for (char bit : text) {
            currentBits += bit;
            if (containsBits(currentBits)) {
                result += getSymbol(currentBits);
                currentBits.clear();
            }
        }

        return result;
    }

    std::string decode(std::string bits, std::map<char, int> amounts) {
        text = bits;
        setInitialState(bits, amounts);
        return decode();
    }
};
