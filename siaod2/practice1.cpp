#include <iostream>
#include <bitset>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

using steady_clock = std::chrono::steady_clock;

void task1_1();
void task1_2();
void task1_3();
void task2_1();
void task2_2();
void task2_3();
void fillFile(std::string, const int);
void task3_1();
void task3_2();

template <class T>
void printBitmapMemorySize(long n) {
    const unsigned long bitmapLength    = sizeof(T) * CHAR_BIT,
                        bitmapArrLength = (n - 1) / bitmapLength + 1;

    const unsigned long bitmapMemorySize = bitmapArrLength * bitmapLength;
    std::cout << "Bitmap array is\n" << bitmapMemorySize << " bits\n"
        << bitmapMemorySize / 8 << " B\n" << bitmapMemorySize / 8192 << " KB";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    auto begin = steady_clock::now();
    task3_2();
    auto end = steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    std::cout << "\nSorting worked for " << total.count() << " s";

    return 0;
}


void task1_1() {
    unsigned char x = 255;      // 8-разрядное двоичное число 11111111
    unsigned char mask = 1;     // 1=00000001 – 8-разрядная маска

    std::cout << "Before: " << std::bitset<sizeof(x)* CHAR_BIT>(x);

    x = x & (~(mask << 4));     // результат x=239

    std::cout << "\nAfter: " << std::bitset<sizeof(x)* CHAR_BIT>(x);
}


void task1_2() {
    unsigned char x = 16;       // 8-разрядное число 00010000
    unsigned char mask = 1;     // маска

    std::cout << "Before: " << std::bitset<sizeof(x)* CHAR_BIT>(x);

    x = x | (mask << 7);        // результат x=144 

    std::cout << "\nAfter: " << std::bitset<sizeof(x)* CHAR_BIT>(x);
}


void task1_3() {
    unsigned x = 25;
    const int n = sizeof(int) * 8;      // = 32 - количество разрядов в числе типа int
    unsigned mask = (1 << (n - 1));     // 1 в старшем бите 32-разрядной сетки

    std::cout << "Начальный вид маски: " << std::bitset<n>(mask) 
        << "\nРезультат: ";

    for (int i = 1; i <= n; ++i) {      // 32 раза - по количеству разрядов
        std::cout << ((x & mask) >> (n - i));
        mask >>= 1;     // смещение 1 в маске на разряд вправо
    }
}

void task2_1() {
    const int       numsLength = 8;     // кол-во чисел
    unsigned char   bitmap = 0,         // битовая последовательность
                    mask = 1;           // маска
    unsigned        nums[numsLength];

    for (int i = 0; i < numsLength; ++i) {
        std::cin >> nums[i];
    }

    for (int i = 0; i < numsLength; ++i) {
        bitmap = bitmap | (mask << nums[i]);    // установка в "1" бита в позиции nums[i]
    }

    std::cout << "Result: ";
    for (int i = 0; i < numsLength; ++i) {
        if (bitmap & (mask << i))       // если соответствующий бит установлен в "1"
            std::cout << i << " ";      // позиция бита в битовом числе - исходное число
    }
}

void task2_2() {
    const int           numsLength = 64;
    unsigned long long  bitmap = 0;
    unsigned            nums[numsLength];

    for (int i = 0; i < numsLength; ++i) {
        nums[i] = i;
    }

    // Перетасовка
    std::mt19937_64 mt(time(0));
    std::shuffle(std::begin(nums), std::end(nums), mt);

    for (int i = 0; i < numsLength; ++i) {      // Исходный массив
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < numsLength; ++i) {
        bitmap = bitmap | (1ULL << nums[i]);
    }

    std::cout << "Result: ";
    for (int i = 0; i < numsLength; ++i) {
        if (bitmap & (1ULL << i))
            std::cout << i << " ";
    }
}

void task2_3() {
    const int       numsLength      = 64;
    const unsigned  bitmapLength    = sizeof(unsigned char) * CHAR_BIT,    // размер элемента массива
                    bitmapArrLength = (numsLength - 1) / bitmapLength + 1; // длина битового массива 
    unsigned char   bitmapArr[bitmapArrLength], 
                    mask            = 1;
    unsigned        nums[numsLength];

    for (int i = 0; i < bitmapArrLength; ++i) {     // обнуление битового массива
        bitmapArr[i] = 0;
    }
    for (int i = 0; i < numsLength; ++i) {
        nums[i] = i;
    }

    // Перетасовка
    std::mt19937_64 mt(time(0));
    std::shuffle(std::begin(nums), std::end(nums), mt);

    for (int i = 0; i < numsLength; ++i) {
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";

    unsigned bitmapArrIndex, bitmapArrOffset;   // для каждого числа: индекс внутри bitmapArr
                                                // и смещение внутри элемента bitmapArr
    for (int i = 0; i < numsLength; ++i) {
        bitmapArrOffset             = nums[i] % bitmapLength;
        bitmapArrIndex              = nums[i] / bitmapLength;
        bitmapArr[bitmapArrIndex]   = bitmapArr[bitmapArrIndex] | (mask << bitmapArrOffset);
    }

    std::cout << "Result: ";
    for (int i = 0; i < numsLength; ++i) {
        if (bitmapArr[i / bitmapLength] & (mask << (i % bitmapLength)))
            std::cout << i << " ";
    }
}

void fillFile(std::string fileName, const int numsLength) {
    std::ofstream out(fileName);

    if (!out.is_open()) {
        std::cout << "\nFile error!";
        return;
    }

    unsigned long *nums = new unsigned long[numsLength];
    for (int i = 0; i < numsLength; ++i) {
        nums[i] = i;
    }

    // Перетасовка
    std::mt19937_64 mt(time(0));
    std::shuffle(&nums[0], &nums[numsLength], mt);
    
    for (int i = 0; i < numsLength; ++i) {
        out << nums[i] << "\n";
    }

    out.close();
    delete[] nums;
}

void task3_1() {
    std::string fileInput   = "D:\\temp\\vs\\input.txt", 
                fileOutput  = "D:\\temp\\vs\\output.txt";

    std::ifstream in(fileInput);
    if (!in.is_open()) {
        std::cout << "\nFile error!";
        return;
    }
    
    const int           numsLength      = 10000000;
    const unsigned long bitmapLength    = sizeof(unsigned long long) * CHAR_BIT,
                        bitmapArrLength = (numsLength - 1) / bitmapLength + 1;
    unsigned long long  *bitmapArr      = new unsigned long long[bitmapArrLength];
    
    for (int i = 0; i < bitmapArrLength; ++i) {
        bitmapArr[i] = 0;
    }

    unsigned long num;                              // считываемое число
    unsigned long bitmapArrIndex, bitmapArrOffset;  // для каждого числа: индекс внутри bitmapArr
                                                    // и смещение внутри элемента bitmapArr
    while (in >> num) {
        bitmapArrOffset             = num % bitmapLength;
        bitmapArrIndex              = num / bitmapLength;
        bitmapArr[bitmapArrIndex]   = bitmapArr[bitmapArrIndex] | (1ULL << bitmapArrOffset);
    }
    in.close();

    std::ofstream out(fileOutput);
    for (int i = 0; i < numsLength; ++i) {
        if (bitmapArr[i / bitmapLength] & (1ULL << (i % bitmapLength)))
            out << i << "\n";
    } 

    out.close();
    delete[] bitmapArr;
}

void task3_2() {
    printBitmapMemorySize<unsigned long long>(10000000);
    /*const int   numsLength      = 10000000,
                bitmapLength    = sizeof(unsigned long long) * CHAR_BIT,
                bitmapArrLength = (numsLength - 1) / bitmapLength + 1;

    const int bitmapMemorySize = bitmapArrLength * CHAR_BIT;
    std::cout << "Bitmap array is " << bitmapMemorySize << " B or "
        << bitmapMemorySize / 1024 << " KB";*/
}
