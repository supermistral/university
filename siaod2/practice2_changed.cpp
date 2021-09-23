#include <iostream>
#include <string>
#include <ctime>
#define SIZE 10

template <class T>
T generateKey() {       // Генерация ключа в диапазоне 10^12 - (10^13 - 1) 
    return (double)rand() / (RAND_MAX + 1) * 899999999 + 100000000;
}


struct HashmapItemData {
    std::string author;         // автор
    std::string name;           // название

    HashmapItemData() {
        author = this->generate();         // Случайное заполнение
        name = this->generate();
    }

    std::string generate() {
        std::string result = "";
        for (int i = 0; i < 3; ++i) {       // Генерация 3 случайных букв
            char c = rand() % 26 + 97;
            result.push_back(c);
        }
        return result;
    }
};


template<class T1, class T2>
struct Node {
    T1 key;     // ключ
    T2 value;   // информация по ключу

    Node* next = nullptr;    // указатель на следующий узел
};


template<class T1, class T2>
struct LinkedList {
    Node<T1, T2>* head = nullptr;

    ~LinkedList() {
        Node<T1, T2>* next = nullptr;

        while (head != nullptr) {
            next = head->next;
            delete head;
            head = next;
        }
    }

    void addNode(T1 key, T2 value) {
        Node<T1, T2>* newNode = new Node<T1, T2>;
        newNode->key = key;
        newNode->value = value;
        newNode->next = head;
        head = newNode;
    }

    Node<T1, T2>** searchNode(T1 key) {
        for (Node<T1, T2>** temp = &head; *temp; *temp = (*temp)->next) {
            if ((*temp)->key == key) {
                return temp;
            }
        }
        return nullptr;
    }

    void removeNode(T1 key) {
        for (Node<T1, T2>* curr = head, *prev = nullptr; curr; prev = curr, curr = curr->next) {
            if (curr->key == key) {
                if (curr == head) {
                    head = head->next;
                }
                else {
                    prev->next = curr->next;
                }
                delete curr;
                curr = nullptr;
                return;
            }
        }
    }
};


template<class Tkey, class Tval>
struct Hashmap {
    LinkedList<Tkey, Tval>** items;     // указатель на массив указателей на структуру с данными
    int currentSize = 0;                // текущее кол-во элементов
    int maxSize = SIZE;                 // размер таблицы

    Hashmap(int size = SIZE) {
        items = new LinkedList<Tkey, Tval>*[size];

        for (int i = 0; i < size; ++i) {        // обнуление указателей
            items[i] = nullptr;
        }
        for (int i = 0; i < size; ++i) {        // генерация значений
            Tkey key = generateKey<Tkey>();
            Tval value;

            this->add(key, value);
        }
    }

    ~Hashmap() {
        for (int i = 0; i < maxSize; ++i) {
            delete items[i];
        }
        delete[] items;
    }

    // Добавление элемента
    void add(Tkey key, Tval value) {
        ++currentSize;

        if (this->rehashingCondition()) {
            this->rehashing();
        }

        int keyInHashmap = this->hash(key);

        if (!items[keyInHashmap]) {
            items[keyInHashmap] = new LinkedList<Tkey, Tval>();
        }

        items[keyInHashmap]->addNode(key, value);

    }

    void rehashing() {
        this->print();
        maxSize *= 2;
        LinkedList<Tkey, Tval>** newItems = new LinkedList<Tkey, Tval>*[maxSize];

        for (int i = 0; i < maxSize; ++i) {
            newItems[i] = nullptr;
        }

        int keyInHashmap;

        for (int i = 0; i < maxSize / 2; ++i) {
            if (items[i]) {
                for (Node<Tkey, Tval>* node = items[i]->head; node; node = node->next) {
                    keyInHashmap = this->hash(node->key);
                    if (!newItems[keyInHashmap]) {
                        newItems[keyInHashmap] = new LinkedList<Tkey, Tval>();
                    }
                    newItems[keyInHashmap]->addNode(node->key, node->value);
                }
            }
            delete items[i];
        }

        delete[] items;
        items = newItems;

        std::cout << "\n[REHASHING]";
        this->print();
    }

    // Поиск по ключу с возвратом элемента
    Node<Tkey, Tval>** search(Tkey key) {
        int keyInHashmap = this->hash(key);
        if (items[keyInHashmap]) {
            return items[keyInHashmap]->searchNode(key);
        }
        return nullptr;
    }

    // Удаление элемента по ключу
    void remove(Tkey key) {
        int keyInHashmap = this->hash(key);
        if (items[keyInHashmap]) {
            items[keyInHashmap]->removeNode(key);
        }
    }

    // Хеш-функция 
    int hash(Tkey key) {
        return key % maxSize;
    }

    bool rehashingCondition() {
        return (currentSize / maxSize) > 0.75;
    }

    // Вывод таблицы
    void print() {
        for (int i = 0; i < maxSize; ++i) {
            if (items[i] != nullptr) {
                std::cout << "\n" << i << " | " << *items[i];
            }
        }
    }
};

// перегрузка операторов для ввода и вывода
std::istream& operator>> (std::istream& in, HashmapItemData& item) {
    in >> item.author >> item.name;
    return in;
}

std::ostream& operator<< (std::ostream& out, const HashmapItemData& item) {
    out << item.author << " " << item.name;
    return out;
}

template <class T1, class T2>
std::ostream& operator<< (std::ostream& out, const Node<T1, T2>& item) {
    out << item.key << ": " << item.value;
    return out;
}

template <class T1, class T2>
std::ostream& operator<< (std::ostream& out, const LinkedList<T1, T2>& item) {
    if (!item.head) {
        out << "Empty";
        return out;
    }
    std::cout << *item.head;
    for (Node<T1, T2>* temp = item.head->next; temp; temp = temp->next) {
        out << " -> " << *temp;
    }
    return out;
}


int main()
{
    srand(static_cast<unsigned>(time(0)));

    Hashmap<long, HashmapItemData> map(25);
    map.print();

    long key;
    std::cout << "\n\nKey to remove >> ";
    std::cin >> key;

    Node<long, HashmapItemData>** item = map.search(key);
    if (item) {
        std::cout << **item << " | Address " << *item << "\nRemoving...\n";
        map.remove(key);
        std::cout << "Address " << **item;
    }

    return 0;
}
