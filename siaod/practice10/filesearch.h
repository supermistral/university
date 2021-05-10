// main.cpp
#include <ctime>
#include "filesearch.h"
#include <chrono>


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::string fileName = "D:\\forwork\\siaod10\\input.bin",
        fileStationsName = "D:\\forwork\\siaod10\\stations.txt";
    const int keyRangeMin = 1,      // нижняя граница диапазона ключа
        keyRangeMax = 100000;       // верхняя граница

    FileSearch fileObj(fileName);
    if (!fileObj.checkFile())
        return -2;
    fileObj.generate(keyRangeMin, keyRangeMax, fileStationsName);
    //fileObj.printFile();

    int key;
    std::cout << "Key to search = "; std::cin >> key;
    //auto begin = std::chrono::steady_clock::now();
    //fileObj.runSearchLinear(key);
    fileObj.runSearchBinary(key);
    //auto end = std::chrono::steady_clock::now();
    //auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //std::cout << "\n" << total.count() << " mcs\n";

    //auto begin = std::chrono::steady_clock::now();
    //fileObj.runSearchLinear(key);
    //auto end = std::chrono::steady_clock::now();
    //auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //std::cout << "\n" << total.count() << " mcs";
}
