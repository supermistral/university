#include <iostream>
#include <string>
#include <ctime>
#define MAX_SIZE 1000000000000
#define MIN_SIZE 100000000000


template <class T>
T generateKey() {       // Генерация ключа в диапазоне 10^11 - (10^12 - 1) 
    return (double)rand() / (RAND_MAX + 1) * (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
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
    Node<T1, T2>* head = nullptr;       // первый в списке

    ~LinkedList() {
        Node<T1, T2>* next = nullptr;

        while (head != nullptr) {
            next = head->next;
            delete head;
            head = next;
        }
    }

    // Добавление узла
    void addNode(T1 key, T2 value) {
        Node<T1, T2>* newNode = new Node<T1, T2>;
        newNode->key = key;
        newNode->value = value;
        newNode->next = head;       // вставка в начало
        head = newNode;
    }

    // Поиск узла
    Node<T1, T2>* searchNode(T1 key) {
        for (Node<T1, T2>* temp = head; temp; temp = temp->next) {
            if (temp->key == key) {
                return temp;
            }
        }
        return nullptr;
    }

    // Удаление узла
    void removeNode(T1 key) {
        for (
            Node<T1, T2>* curr = head, *prev = nullptr; 
            curr; 
            prev = curr, curr = curr->next
        ) {
            if (curr->key == key) {
                if (curr == head) {     // если удалить первый в списке
                    head = head->next;  // то первому присвоить следующий за ним
                }
                else {                          // иначе установить связь между
                    prev->next = curr->next;    // предыдущим и следующим
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
    LinkedList<Tkey, Tval>** items;     // указатель на массив указателей на списки
    int currentSize = 0;                // текущее кол-во элементов
    int maxSize;                        // размер таблицы

    Hashmap(int size) {
        maxSize = size;
        items = new LinkedList<Tkey, Tval> * [size];

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

    // Рехеширование
    void rehashing() {
        maxSize *= 2;           // новая таблица в 2 раза больше
        LinkedList<Tkey, Tval>** newItems = new LinkedList<Tkey, Tval> * [maxSize];

        for (int i = 0; i < maxSize; ++i) {
            newItems[i] = nullptr;
        }

        int keyInHashmap;

        for (int i = 0; i < maxSize / 2; ++i) { // итерация по всем элементам до операции
            if (items[i]) {
                for (Node<Tkey, Tval>* node = items[i]->head; node; node = node->next) {
                    keyInHashmap = this->hash(node->key);       // пересчет хеша и добавление
                    if (!newItems[keyInHashmap]) {              // в новую таблицу
                        newItems[keyInHashmap] = new LinkedList<Tkey, Tval>();
                    }
                    newItems[keyInHashmap]->addNode(node->key, node->value);
                }
            }
            delete items[i];
        }

        delete[] items;
        items = newItems;       // переприсвоение таблицы
    }

    // Поиск по ключу с возвратом элемента
    Node<Tkey, Tval>* search(Tkey key) {
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

    // Коэффициент нагрузки
    bool rehashingCondition() {
        return (double)currentSize / maxSize > 0.75;
    }

    // Вывод таблицы
    void print() {
        for (int i = 0; i < maxSize; ++i) {
            if (items[i] != nullptr) {
                std::cout << i << " | " << *items[i] << "\n";
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


void task() {
    std::string command;
    long long key;
    Hashmap<long long, HashmapItemData> *map = nullptr;

    std::cout << "Work with hashmap\n---------\n"
        << "gen <size>\n"
        << "add <number> <author> <name>\n"
        << "del <number>\n"
        << "search <number>\n"
        << "print\n"
        << "exit\n"
        << "---------\n";

    while (1) {
        std::cin >> command;
        if (command == "gen") {
            int size;
            std::cin >> size;
            delete map;
            map = new Hashmap<long long, HashmapItemData>(size);
        }
        else if (command == "exit") {
            break;
        }
        else if (map) {
            if (command == "add") {
                HashmapItemData data;
                std::cin >> key >> data;
                map->add(key, data);
            }
            else if (command == "del") {
                std::cin >> key;
                map->remove(key);
            }
            else if (command == "search") {
                std::cin >> key;
                Node<long long, HashmapItemData>* node = map->search(key);
                if (node) {
                    std::cout << "Found: " << *node << "\n";
                }
                else {
                    std::cout << "Not found\n";
                }
            }
            else if (command == "print") {
                map->print();
            }
        }
        else {
            std::cout << "Wrong command\n";
        }
        std::cout << "\n";
    }

    delete map;
}


int main()
{
    srand(static_cast<unsigned>(time(0)));

    task();

    return 0;
}
