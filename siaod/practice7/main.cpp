#include <iostream>
#include "node.h"

void fillWithKnoweldgeAreas(List& list, ListKnowledgeArea*& listArea, int size) {
    std::cout << "Number of areas = " << size << "\n";
    for (Node* temp = list.head, int i = 0; temp; temp = temp->next, ++i) {
        std::string line;
        std::cout << i << ": ";
        std::cin >> line;
        while (line != "0") {
            pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
                temp->data.knowledgeArea, line
            );
            std::cin >> line;
        }
    }
}


int main()
{
    int size;
    List list;
    ListKnowledgeArea listKnowledgeArea;
    ListKnowledgeArea* listKnowledgeAreaForList;
    std::string commands[] = {
        "create",
        "create knowledge",
        "print",
        "print reverse",
        "print knowledge",
        "print knowledge reverse",
        "search",
        "push back",
        "create knowledge area",
        "remove",
        "move"
    };
    std::string line;
    std::getline(std::cin, line);
    while (line != "exit") {
        if (line == commands[0])
            list = createList(size);
        else if (line == commands[1])
            fillWithKnoweldgeAreas(list, listKnowledgeAreaForList, size);
        else if (line == commands[2])
            printFromLeftToRight(list.head);
        else if (line == commands[3])
            printFromRightToLeft(list.last);
        else if (line == commands[4]) {
            for (int i = 0; i < size; ++i) {
                std::cout << i << ": ";
                printFromLeftToRight(listKnowledgeAreaForList[0].head);
            }
        }
        else if (line == commands[5]) {
            for (int i = 0; i < size; ++i) {
                std::cout << i << ": ";
                printFromRightToLeft(listKnowledgeAreaForList[0].head);
            }
        }
        else if (line == commands[6]) {

        }
        else if (line == commands[7]) {
            BookData data;
            ListKnowledgeArea newList;
            std::cout << "New book data: ";
            std::cin >> data;
            std::cout << "New knowledge areas: ";
            std::string line;
            std::cin >> line;
            while (line != "0") {
                pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
                    newList, line
                );
                std::cin >> line;
            }
            data.knowledgeArea = newList;
            pushBack(list, data);
        }
        else if (line == commands[8]) {

        }
        std::cout << "done!\n\n";
        std::getline(std::cin, line);
    }
    
    delete[] listKnowledgeAreaForList;

    return 0;
}
