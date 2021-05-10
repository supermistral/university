// filesearch.h
#pragma once
#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::string> string_arr;

class FileSearch {
    int         numberOfRecords = 10;
    std::string file;

public:
    struct Record {
        struct Date {
            short day, month, year,
                hour, minute;

            Date();
            std::string getString();
        };

        int     number;
        char    stationDep[21],
                stationDest[21],
                date[16];

        Record() {};
        Record(int, string_arr);

        friend std::ostream& operator<< (std::ostream&, const Record&);
    };

    struct TableNode {
        int key,
            refToRecord;
        TableNode() {};
        TableNode(int key, int ref)
            : key(key), refToRecord(ref) {};
    };

    struct Table {
        TableNode* table;
        int size;

        Table(Record*, int);
        ~Table();

        void quickSort(int, int);
    };

    FileSearch(std::string);

    void generate(int, int, std::string);
    void printFile();
    bool checkFile();
    Record* getRecords();

    Record searchLinear(int);
    void runSearchLinear(int);

    int searchBinary(int, Table&);
    Record getRecordFromRef(int);
    void runSearchBinary(int);
};
