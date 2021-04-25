// main.cpp

#include <iostream>
#include "node.h"

int main()
{
    int size = 0;
    List* list = nullptr;
    ListKnowledgeArea* listKnowledgeArea = nullptr;
    std::string line;

    while (std::getline(std::cin, line) && line != "exit") {
        if (line == "create") {
            list = createList(size);
            std::cout << "\nKnowledge area lists:\n";
            fillWithKnoweldgeAreas(list->head);
        }
        else if (line == "print") {
            printFromLeftToRight(list->head);
        }
        else if (line == "print reverse") {
            printFromRightToLeft(list->last);
        }
        else if (line == "print area") {
            printKnowledgeAreasFromLeftToRight(list->head);
        }
        else if (line == "print area reverse") {
            printKnowledgeAreasFromRightToLeft(list->last);
        }
        else if (line == "search") {
            int id;
            std::cout << "Id to search = "; std::cin >> id;
            Node* node = searchNode(list->head, id);

            if (node)
                std::cout << "Node was found -> " << node << "\n";
            else
                std::cout << "Node wasn't found\n";
        }
        else if (line == "push back") {
            BookData data;
            std::string nameLine;
            std::cout << "New book data: "; std::cin >> data;
            std::cout << "New knowledge areas: "; 
       
            while ((std::cin >> nameLine) && nameLine != "0") {
                pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
                    data.knowledgeArea, nameLine
                );
            }
            pushBack(list, data);
        }
        else if (line == "create new area") {
            listKnowledgeArea = createListKnowledgeArea(list->head);
            printFromLeftToRight(listKnowledgeArea->head);
        }
        else if (line == "remove") {
            std::string author;
            int year;
            std::cout << "Author = "; std::cin >> author;
            std::cout << "Year = "; std::cin >> year;

            removeNodes(list, author, year);
        }
        else if (line == "move") {
            int id;
            std::cout << "Id = "; std::cin >> id;

            moveNodes(list, id);
            printFromLeftToRight(list->head);
        }
        std::cout << "\n";
    }
    
    delete list;
    delete listKnowledgeArea;

    return 0;
}
