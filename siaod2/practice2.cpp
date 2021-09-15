#include <iostream>
#include <string>
#include <ctime>
#define SIZE 13

template <class T>
T generateKey() {       // Генерация ключа в диапазоне 10^7 - (10^8 - 1) 
    return (double)rand() / (RAND_MAX + 1) * 8999999 + 1000000;
}


struct HashmapItemData {
    std::string fio;        // ФИО
    std::string address;    // Адрес

    HashmapItemData() {
        fio = this->generate();         // Случайное заполнение
        address = this->generate();
    }

    std::string generate() {
        std::string result = "";
        for (int i = 0; i < 3; ++i) {   // Генерация 3 случайных букв
            char c = rand() % 26 + 97;
            result.push_back(c);
        }
        return result;
    }
};


template<class T1, class T2>
struct HashmapItem {
    T1 key;     // ключ
    T2 value;   // информация по ключу
};


template<class Tkey, class Tval>
struct Hashmap {
    HashmapItem<Tkey, Tval> *items[SIZE];   // массив указателей на структуру с данными
    int currentSize = 0;                    // текущий размер таблицы

    Hashmap() {
        for (int i = 0; i < SIZE; ++i) {        // обнуление указателей
            items[i] = nullptr;
        }
        for (int i = 0; i < SIZE; ++i) {        // генерация значений
            Tkey key = generateKey<Tkey>();
            Tval value;

            this->add(key, value);
        }
    }

    ~Hashmap() {
        for (int i = 0; i < SIZE; ++i) {
            delete items[i];
        }
    }

    // Вставка элемента
    void insert(HashmapItem<Tkey, Tval> *item) {
        int i = 0;
        int keyInHashmap = hash(item->key, i);

        if (currentSize < SIZE) {                   // есть куда вставлять
            if (items[keyInHashmap] == nullptr) {   // ячейка пуста - вставка
                items[keyInHashmap] = item; 
            }
            else if (items[keyInHashmap]->key == item->key) {   // ключ повторился - выход
                return;
            }
            else {
                do {                                        // вычислять новый индекс
                    keyInHashmap = hash(item->key, ++i);    // пока не встретится свободная
                } while (items[keyInHashmap] != nullptr);   // ячейка

                items[keyInHashmap] = item;
            }
        }
        else {
            return;
        }

        ++currentSize;
    }

    // Добавление элемента (создание + вставка)
    void add(Tkey key, Tval value) {
        HashmapItem<Tkey, Tval> *item = new HashmapItem<Tkey, Tval>;
        item->key = key;
        item->value = value;
        std::cout << "\n" << *item << " | HASH";

        this->insert(item);
    }

    // Поиск по ключу с возвратом индекса в таблице
    int search_index(Tkey key) {
        int i = 0;
        int keyInHashmap;
        const int firstKeyInHashmap = this->hash(key, i);       // первый индекс по данному ключу

        do {                                            // вычислять новый индекс
            keyInHashmap = this->hash(key, i++);        // пока не встретится нужная ячейка
            if (
                items[keyInHashmap] == nullptr ||               // если встретилась нулевое
                i != 1 && keyInHashmap == firstKeyInHashmap     // или индекс повторяется - выход
            ) {      
                return -1;
            }
        } while (items[keyInHashmap]->key != key);

        return keyInHashmap;
    }

    // Поиск по ключу с возвратом элемента
    HashmapItem<Tkey, Tval>** search(Tkey key) {
        int index = this->search_index(key);
        if (index < 0) {
            return nullptr;
        }
        return &items[index];
    }

    // Удаление элемента по ключу
    void remove(Tkey key) {
        int index = this->search_index(key);
        if (index >= 0) {
            delete items[index];
            items[index] = nullptr;
        }
    }

    // Функция f(key)
    int hashKey(Tkey key) {
        return key % SIZE;
    }

    // Функция h(key)
    int hashOffset(Tkey key) {
        return 1 + key % (SIZE - 2);
    };
    
    // Хеш-функция 
    int hash(Tkey key, int i) {
        int result = (this->hashKey(key) + i * this->hashOffset(key)) % SIZE;
        //std::cout << " -> " << result;
        return result;
    }

    // Вывод таблицы
    void print() {
        for (int i = 0; i < SIZE; ++i) {
            if (items[i] != nullptr) {
                std::cout << "\n" << i << " -> " << *items[i];
            }
        }
    }
};

// перегрузка операторов для ввода и вывода
std::istream& operator>> (std::istream& in, HashmapItemData& item) {
    in >> item.fio >> item.address;
    return in;
}

std::ostream& operator<< (std::ostream& out, const HashmapItemData& item) {
    out << item.fio << " " << item.address;
    return out;
}

template <class T1, class T2>
std::ostream& operator<< (std::ostream& out, const HashmapItem<T1, T2>& item) {
    out << item.key << ": " << item.value;
    return out;
}


int main()
{
    srand(static_cast<unsigned>(time(0)));

    Hashmap<int, HashmapItemData> map;
    std::cout << "\n";
    map.print();

    int key;
    std::cout << "\n\nKey to remove >> ";
    std::cin >> key;
    
    HashmapItem<int, HashmapItemData> *&item = *map.search(key);
    if (item) {
        std::cout << *item << " | Address " << item << "\nRemoving...\n";
        map.remove(key);
        std::cout << "Address " << item;
    }
    
    return 0;
}
