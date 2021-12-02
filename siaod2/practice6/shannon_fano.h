#pragma once
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>


class ShannonFano {
    struct symbolNode {
        int amount;
        std::string bits;
    };

    int size = 0;                       // размер алфавита
    char* symbols;                      // алфавит
    std::string text;                   // исходный текст
    std::map<char, symbolNode> bitsMap; // таблица символов с вхождениями и битовым кодом

    // рекурсивное заполнение таблицы символов
    void encodeInternal(int start, int end) {
        if (start == end) {     // конец разбиения
            return;
        }
        else if (end - start == 1) {    // группа из 2ух символов
            bitsMap[symbols[start]].bits += '0';
            bitsMap[symbols[end]].bits += '1';
        }
        else {
            int currentAmount = 0,      // текущая сумма вхождений
                divisionCenter = -1;    // индекс центрального элемента в алфавите в разбиении
            float total = 0,            // половина от всех вхождений в разбиении
                diff = FLT_MAX,         // (i-1) разница между текущей суммой и total
                currentDiff;            // i-ая разница

            for (int i = start; i <= end; ++i) {
                total += bitsMap[symbols[i]].amount;
            }

            total /= 2;

            for (int i = start; i <= end; ++i) {
                currentAmount += bitsMap[symbols[i]].amount;
                currentDiff = std::abs(total - currentAmount);

                if (currentDiff <= diff) {      // разница не больше предыдущей - верхняя группа 
                    bitsMap[symbols[i]].bits += '0';    // присвоить верхней группе 0
                }
                else {
                    bitsMap[symbols[i]].bits += '1';    // присвоить нижней группе 1
                    if (divisionCenter < 0) {   // первый элемент в нижней группе 
                        divisionCenter = i;     //   - назначить индекс разбиения
                    }
                }
                diff = currentDiff;
            }

            if (divisionCenter < 0) {
                divisionCenter = start + 1;
            }

            encodeInternal(start, divisionCenter - 1);
            encodeInternal(divisionCenter, end);
        }
    }

    void clear() {
        bitsMap.clear();
        delete symbols;
        size = 0;
    }

    // заполнение таблицы символов по тексту - установка вхождений
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

    // заполнение алфавита и сортировка по убыванию вхождений
    void setSymbols() {
        size = bitsMap.size();
        symbols = new char[size];
        int ind = 0;

        for (auto const& p : bitsMap) {
            symbols[ind++] = p.first;
        }

        std::sort(
            symbols,
            symbols + size,
            [this](const char a, const char b) {
                return bitsMap[a].amount > bitsMap[b].amount;
            }
        );
    }

    // начальная инициализация по тексту
    void setInitialState(std::string text) {
        clear();
        this->text = text;

        setBitsMap();
        setSymbols();
    }

    // начальная инициализация по тексту и таблице вхождений
    void setInitialState(std::string text, std::map<char, int> amounts) {
        clear();
        this->text = text;

        setBitsMap(amounts);
        setSymbols();
    }

    // проверка на существование битовой последов-ти в таблице символов
    bool containsBits(std::string bits) {
        for (const auto& p : bitsMap) {
            if (p.second.bits == bits) {
                return true;
            }
        }
        return false;
    }

    // получение символа по битовой последов-ти
    char getSymbol(std::string bits) {
        for (const auto& p : bitsMap) {
            if (p.second.bits == bits) {
                return p.first;
            }
        }
        return '\0';
    }

public:
    // кодирование
    void encode() {
        if (size == 0) 
            return;

        encodeInternal(0, size - 1);
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

    // вывод информации о кодировании
    void printEncodedString() {
        for (int i = 0; i < size; ++i) {
            std::cout << "\n" << symbols[i] << " " << bitsMap[symbols[i]].amount
                << " " << bitsMap[symbols[i]].bits;
        }

        std::string result = getEncodedText();

        std::cout << "\nEncoded message: " << result
            << "\nBits: " << result.size()
            << "\nSource text size: " << text.size() * 8 << "\n";
    }

    // чтение файла и иницализация прочитанным текстом
    bool readFile(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            file.close();
            return false;
        }

        std::string line;
        std::string text;
        while (std::getline(file, line)) {
            text += line;
        }

        file.close();
        setInitialState(text);

        return true;
    }

    ~ShannonFano() {
        clear();
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

        file << getEncodedText();           // запись сжатого текста

        for (const auto& p : bitsMap) {     // запись символа и кол-ва его вхождений
            file << "\n" << p.first << " " << p.second.amount;
        }

        return true;
    }

    // декодирование
    std::string decode() {
        encode();

        for (const auto& p : bitsMap) {     // показ битовых кодов символов
            std::cout << "\n" << p.first << " " << p.second.bits;
        }

        std::string currentBits = "",
            result = "";

        for (char bit : text) {         // поиск по сжатому тексту
            currentBits += bit;
            if (containsBits(currentBits)) {        // символ найден
                result += getSymbol(currentBits);   // добавить символ к тексту
                currentBits.clear();
            }
        }

        return result;
    }
};
