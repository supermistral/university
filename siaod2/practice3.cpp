#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>


const int ALPHABET_LENGTH = 256;
const int CHUNK_SIZE = 1000;


struct FileManager {
    std::ifstream input;
    int patternSize,
        fileSize;

    bool open(std::string fileName) {
        input.open(fileName, std::ios::binary);

        return input.is_open();
    }

    std::string getPattern() {
        std::string pattern;
        std::getline(input, pattern);
        pattern.pop_back();

        patternSize = pattern.length();

        int curPos = input.tellg();
        input.seekg(0, std::ios::end);
        fileSize = input.tellg();
        input.seekg(curPos, std::ios::beg);

        return pattern;
    }

    std::string getText() {
        int curPos = input.tellg();

        if (curPos < 0) {
            return "";
        }

        std::string text;
        if (fileSize - curPos >= CHUNK_SIZE) {
            text.resize(CHUNK_SIZE);
            input.read(&text[0], CHUNK_SIZE);               // чтение кусками
            input.seekg(-patternSize + 1, std::ios::cur);   // перекрытие шаблона
        }
        else {
            int diff = fileSize - input.tellg();
            text.resize(diff);
            input.read(&text[0], diff);
        }

        return text;
    }

    ~FileManager() {
        input.close();
    }
};


std::vector<std::string> getWords(std::string, std::string, int&);
void printVector(std::vector<std::string>);
void printVector(std::vector<int>);
std::vector<int> badCharHeuristic(std::string);
std::vector<int> goodSuffixHeuristic(std::string);
void turbo_bm_search(std::string, std::string, std::vector<int>, std::vector<int>, int, int&);


int main()
{
    setlocale(LC_ALL, "RUS");

    /*std::string text = "abcdefggthcvd, asdv, grdrgdf, abdrdrtysd, yasavacvxcv, asfdweg, sadafg, basvabc, sderdgs, abcddwewet",
        pattern = "abcdefggth";

    std::string largeText = "";
    for (int i = 0; i < 1000; ++i) {
        largeText += text;
    }
        
    std::cout << "Size of text = " << largeText.size()
        << "\nSize of pattern = " << pattern.size();

    int comps = 0;
    auto begin = std::chrono::steady_clock::now();
    std::vector<std::string> result = getWords(pattern, largeText, comps);
    auto end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "\n\n" << total.count() << " ms\nComparisons: " << comps;
    
    //printVector(result);*/

    std::string fileName = "D:\\forwork\\siaod5\\input.txt";

    FileManager fileManager;
    if (!fileManager.open(fileName)) {
        std::cout << "File error!";
        return 1;
    }

    std::string pattern = fileManager.getPattern();

    auto begin = std::chrono::steady_clock::now();

    std::vector<int> badChar = badCharHeuristic(pattern);
    std::vector<int> suffShift = goodSuffixHeuristic(pattern);

    std::string textFromFile;
    int counter = 0;
    int comps = 0;

    while ((textFromFile = fileManager.getText()).length() != 0) {
        turbo_bm_search(pattern, textFromFile, badChar, suffShift, counter, comps);
        ++counter;
    }

    auto end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    
    std::cout << "\n\n" << total.count() << " ms\nComparisons: " << comps;

    return 0;
}


void printVector(std::vector<std::string> arr) {
    std::cout << "\n\n";
    for (std::string item : arr) {
        std::cout << item << " ";
    }
}

void printVector(std::vector<int> arr) {
    std::cout << "\n\n";
    for (int item : arr) {
        std::cout << item << " ";
    }
}

std::vector<std::string> getWords(std::string pattern, std::string text, int &comps) {
    std::vector<std::string> words;
    std::string word;

    int n = text.length(), m = pattern.length(), 
        pos, shift = 0;

    while (shift <= n - m) {
        pos = 0;
        comps += 3;
        if (text[pos + shift] == 32 || text[pos + shift] == 44) {   // пробел/запятая
            ++shift;
        }
        else {
            while (pos < m && pattern[pos] == text[pos + shift]) {  // совпадения
                ++pos;
                comps += 2;
            }
            if (pos == m) {             // совпал весь шаблон
                word = pattern;         // слово включает шаблон
                while (                 // добавлять символы пока не встретится
                    pos + shift < n &&          // пробел/запятая
                    text[pos + shift] != 32 && 
                    text[pos + shift] != 44
                ) {
                    word.push_back(text[pos + shift]);
                    ++pos;
                    comps += 3;
                }
                words.push_back(word);
            }
            else {                      // шаблон не совпал
                while (                 // пустой просмотр текущего слова
                    pos + shift < n &&
                    text[pos + shift] != 32 &&
                    text[pos + shift] != 44
                ) {
                    ++pos;
                    comps += 3;
                }
            }
            comps += 1;
            shift += pos;
        }
    }

    return words;
}

// таблица стоп-символов
std::vector<int> badCharHeuristic(std::string s) {
    std::vector<int> badChar(ALPHABET_LENGTH);
    int m = s.length();

    for (int i = 0; i < ALPHABET_LENGTH; ++i) {     // для каждого символа алфавита
        badChar[i] = m;
    }
    for (int i = 0; i < m - 1; ++i) {
        badChar[(int)s[i]] = m - i - 1;
    }

    return badChar;
}

// таблица хороших суффиксов
std::vector<int> goodSuffixHeuristic(std::string s) {
    int m = s.length();
    std::vector<int> suffixShift(m + 1, m);
    std::vector<int> z(m, 0);       // z-функция

    for (int i = 1, maxZidx = 0, maxZ = 0; i < m; ++i) {
        if (i <= maxZ) {
            z[i] = std::min(maxZ - i + 1, z[i - maxZidx]);
        }
        while (i + z[i] < m && s[m - 1 - z[i]] == s[m - 1 - i - z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > maxZ) {
            maxZidx = i;
            maxZ = i + z[i] - 1;
        }
    }

    for (int i = m - 1; i > 0; --i) {
        suffixShift[m - z[i]] = i;
    }
    for (int i = 0, r = 0; i <= m - 1; ++i) {
        if (i + z[i] == m) {
            for (; r <= i; ++r) {
                if (suffixShift[r] == m) {
                    suffixShift[r] = i;
                }
            }
        }
    }

    return suffixShift;
}

void turbo_bm_search(
    std::string pattern, std::string text,
    std::vector<int> badChar, std::vector<int> suffixShift,
    int counter, int &comps
) {
    int n = text.length(), m = pattern.length();
    int prevSuffix = 0, curSuffix, badCharShift,
        shift = m, pos, turboShift;

    for (int textOffset = 0; textOffset <= n - m; ) {
        pos = m - 1;

        while (pos >= 0 && pattern[pos] == text[pos + textOffset]) {
            --pos;
            comps += 2;
            if (prevSuffix != 0 && pos == m - 1 - shift) {
                pos -= prevSuffix;
                comps += 2;
            }
        }

        if (pos < 0) {
            //std::cout << "\nFound on: " << textOffset + counter * CHUNK_SIZE << "\n";
            shift = suffixShift[0];
            prevSuffix = m - shift;
        }
        else {
            curSuffix       = m - 1 - pos;
            turboShift      = prevSuffix - curSuffix;
            badCharShift    = badChar[text[pos + textOffset]] - curSuffix;
            shift           = std::max(std::max(turboShift, badCharShift), suffixShift[pos + 1]);

            if (shift == suffixShift[pos + 1]) {
                prevSuffix = std::min(m - shift, curSuffix);
            }
            else {
                if (turboShift < badCharShift) {
                    shift = std::max(shift, prevSuffix + 1);
                }
                ++comps;
                prevSuffix = 0;
            }
            ++comps;
        }
        comps += 2;

        textOffset += shift;

        //std::cout << textOffset + counter * CHUNK_SIZE << " ";     // вывод индекса строки
    }
}
