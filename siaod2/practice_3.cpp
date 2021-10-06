#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>


const int ALPHABET_LENGTH = 256;
const int CHUNK_SIZE = 100;


struct FileManager {
    std::ifstream input;
    int patternSize;

    FileManager(int size) {
        patternSize = size;
    }

    bool open(std::string fileName) {
        input.open(fileName, std::ios::binary);

        return input.is_open();
    }

    std::string getText() {
        std::string text;
        text.resize(CHUNK_SIZE);
        if (input.read(&text[0], CHUNK_SIZE)) {
            input.seekg(-patternSize + 1, std::ios::cur);
            return text;
        }
        return "";
    }

    ~FileManager() {
        input.close();
    }
};


std::vector<int> badCharHeuristic(std::string);
std::vector<int> goodSuffHeuristic(std::string);
void bm_search(std::string, std::string, std::vector<int>, std::vector<int>, int);


int main()
{
    std::string text = "aaaaaababba",
        pattern = "consequatur",
        fileName = "D:\\forwork\\siaod5\\input.txt";

    FileManager fileManager(static_cast<int>(pattern.length()));
    if (!fileManager.open(fileName)) {
        std::cout << "File error!";
        return 1;
    }

    std::vector<int> badChar = badCharHeuristic(pattern);
    std::vector<int> suffShift = goodSuffHeuristic(pattern);

    std::string textFromFile;
    int counter = 0;
    while ((textFromFile = fileManager.getText()).length() != 0) {
        bm_search(pattern, textFromFile, badChar, suffShift, counter);
        ++counter;
    }

    return 0;
}


std::vector<int> badCharHeuristic(std::string s) {
    std::vector<int> badChar(ALPHABET_LENGTH);

    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        badChar[i] = -1;
    }
    for (size_t i = 0; i < s.length(); ++i) {
        badChar[(int)s[i]] = i;
    }

    return badChar;
}

std::vector<int> goodSuffHeuristic(std::string s) {
    int m = static_cast<int>(s.length());
    std::vector<int> suffShift(m + 1, m);
    std::vector<int> z(m, 0);

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
        suffShift[m - z[i]] = i;
    }
    for (int i = 0, r = 0; i <= m - 1; ++i) {
        if (i + z[i] == m) {
            for (; r <= i; ++r) {
                if (suffShift[r] == m) {
                    suffShift[r] = i;
                }
            }
        }
    }

    return suffShift;
}

void bm_search(
    std::string pattern, std::string text,
    std::vector<int> badChar, std::vector<int> suffShift,
    int counter
) {
    size_t n = text.length(), m = pattern.length();
    for (int shift = 0, pos; shift < n - m; ) {
        pos = m - 1;
        for (; pos >= 0 && pattern[pos] == text[pos + shift]; --pos);
        if (pos < 0) {
            std::cout << "\nFound on: " << shift + counter * CHUNK_SIZE << "\n";
            ++shift;
        }
        else {
            shift += std::max(suffShift[pos + 1], pos - badChar[text[pos + shift]]);
            std::cout << shift + counter * CHUNK_SIZE << " ";
        }
    }
}
