// filesearch.cpp
#include "filesearch.h"
#include <fstream>
#include <iomanip>
#include <chrono>


std::ostream& operator<< (std::ostream& out, const FileSearch::Record& record) {
    out << std::setw(5) << std::left << record.number << " | " 
        << std::setw(20) << std::right << record.stationDep << " -> " 
        << std::setw(20) << std::left << record.stationDest << " | " 
        << record.date;
    return out;
}

FileSearch::Record::Date::Date() {
    day = rand() % 30 + 1;
    month = rand() % 12 + 1;
    year = 21;
    hour = rand() % 24;
    minute = rand() % 12 * 5;
}

std::string FileSearch::Record::Date::getString() {
    short time[] = { hour, minute, day, month, year };
    std::string timeString = "";

    for (short timeUnit : time) {
        if (timeUnit / 10 == 0)
            timeString += "0";
        timeString += std::to_string(timeUnit) + " ";
    }

    timeString[2] = ':';
    timeString[8] = timeString[11] = '.';

    return timeString;
}

FileSearch::Record::Record(int key, string_arr stations) {
    number = key;
    strcpy_s(stationDep, stations[rand() % stations.size()].c_str());
    strcpy_s(stationDest, stations[rand() % stations.size()].c_str());
    strcpy_s(date, Date().getString().c_str());
}

FileSearch::FileSearch(std::string file)
    : file(file) {
}

void FileSearch::generate(int keyRangeMin, int keyRangeMax, std::string fileStations) {
    std::cout << "Number of records = "; std::cin >> numberOfRecords;

    // Заполнение неповторяющимися возможными ключами
    int offset = keyRangeMax - keyRangeMin;
    std::vector<int> keys(offset);
    for (int i = 0; i < offset; ++i)
        keys[i] = i + keyRangeMin;
    // Перетасовка
    for (int i = 0, j; i < offset; ++i) {
        j = rand() % (offset - i) + i;;
        std::swap(keys[i], keys[j]);
    }

    std::ifstream fileInStations(fileStations);
    string_arr stations;
    std::string stationUnit;
    while (std::getline(fileInStations, stationUnit))
        stations.push_back(stationUnit);
    fileInStations.close();

    std::ofstream fileOut(file, std::ios::binary);
    Record* records = new Record[numberOfRecords];

    for (int i = 0; i < numberOfRecords; ++i)
        records[i] = Record(keys[i], stations);

    //std::cout << records[numberOfRecords - 1] << "\n";

    fileOut.write((char*)records, sizeof(Record) * numberOfRecords);
    fileOut.close();
    delete[] records;
}

void FileSearch::printFile() {
    Record* records = this->getRecords();

    for (int i = 0; i < numberOfRecords; ++i)
        std::cout << records[i] << "\n";
    std::cout << "\n";

    delete[] records;
}

bool FileSearch::checkFile() {
    std::ofstream out(file, std::ios::binary);
    if (!out.is_open()) {
        std::cout << "File error";
        out.close();
        return false;
    }
    out.close();
    return true;
}

FileSearch::Record* FileSearch::getRecords() {
    std::ifstream fileIn(file, std::ios::binary);
    Record* records = new Record[numberOfRecords];
    fileIn.read((char*)records, sizeof(Record) * numberOfRecords);
    fileIn.close();

    return records;
}

FileSearch::Record FileSearch::searchLinear(int key) {
    Record reqRecord;
    Record* records = this->getRecords();

    for (int i = 0; i < numberOfRecords; ++i) {
        if (key == records[i].number) {
            reqRecord = records[i];
            break;
        }
    }
    delete[] records;

    return reqRecord;
}

void FileSearch::runSearchLinear(int key) {
    Record record = this->searchLinear(key);

    if (record.number  < 0) {
        std::cout << "Record wasn't found";
        return;
    }
    std::cout << record;
}

FileSearch::Table::Table(Record* records, int numRecords) {
    size = numRecords;
    table = new TableNode[size];

    for (int i = 0; i < size; ++i)
        table[i] = TableNode(records[i].number, i);
}

FileSearch::Table::~Table() {
    delete[] table;
}

void FileSearch::Table::quickSort(int l, int r) {
    int i = l,
        j = r,
        pivot = table[(l + r) / 2].key;

    while (i <= j) {
        while (table[i].key < pivot)
            ++i;
        while (table[j].key > pivot)
            --j;
        if (i <= j)
            std::swap(table[i++], table[j--]);
    }

    if (j > l)
        this->quickSort(l, j);
    if (i < r)
        this->quickSort(i, r);
}

int FileSearch::searchBinary(int key, Table& hashTable) {
    int delta = hashTable.size,
        i = (delta - 1) / 2;

    while (1) {
        if (hashTable.table[i].key < key) {
            if (delta == 0)
                break;
            delta = (delta - 1) - delta / 2;
            i = i + 1 + delta / 2;
        }
        else if (hashTable.table[i].key > key) {
            if (delta == 0)
                break;
            delta = delta / 2;
            i = i - delta + delta / 2;
        }
        else
            return hashTable.table[i].refToRecord;
    }

    return -1;
}

FileSearch::Record FileSearch::getRecordFromRef(int refToRecord) {
    std::ifstream fileIn(file, std::ios::binary);

    Record record;
    fileIn.seekg(refToRecord * sizeof(Record), std::ios::beg);
    fileIn.read((char*)&record, sizeof(Record));
    fileIn.close();

    return record;
}

void FileSearch::runSearchBinary(int key) {
    Record* records = this->getRecords();

    Table hashTable(records, numberOfRecords);
    hashTable.quickSort(0, numberOfRecords - 1);
    
    //auto begin = std::chrono::steady_clock::now();
    int ref = this->searchBinary(key, hashTable);
    //auto end = std::chrono::steady_clock::now();
    //auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //std::cout << total.count() << " mcs\n";
    
    if (ref < 0) {
        std::cout << "Record wasn't found";
        return;
    }
    //std::cout << this->getRecordFromRef(ref);

    delete[] records;
}
