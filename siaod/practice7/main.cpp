#include <iostream>
#include "node.h"

//void fillWithKnoweldgeAreas(List*& list, ListKnowledgeArea**& listArea, int size) {
//    std::cout << "Number of areas = " << size << "\n";
//    int ind = 0;
//    for (Node* temp = list->head; temp; temp = temp->next, ++ind) {
//        std::string line;
//        std::cout << ind << ": ";
//        std::cin >> line;
//        listArea[ind] = new ListKnowledgeArea;
//        while (line != "0") {
//            pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
//                temp->data.knowledgeArea, line
//            );
//            std::cin >> line;
//        }
//    }
//}


int main()
{
    int size = 0;
    List* list = nullptr;
    ListKnowledgeArea* listKnowledgeArea = nullptr;
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
        if (line == "create") {
            list = createList(size);
        }
        else if (line == "create knowledge") {}
            //fillWithKnoweldgeAreas(list, listKnowledgeAreaForList, size);
        else if (line == "print")
            printFromLeftToRight(list->head);
        else if (line == "print reverse")
            printFromRightToLeft(list->last);
        else if (line == "print knowledge") {
            for (int i = 0; i < size; ++i) {
                std::cout << i << ": ";
                //printFromLeftToRight<NodeKnowledgeArea>(listKnowledgeAreaForList[0]->head);
            }
        }
        else if (line == "print knowledge reverse") {
            for (int i = 0; i < size; ++i) {
                std::cout << i << ": ";
                //printFromRightToLeft<NodeKnowledgeArea>(listKnowledgeAreaForList[0]->head);
            }
        }
        else if (line == "search") {
            BookData dataToSearch;
            std::cout << "Search: "; std::cin >> dataToSearch;
            Node* node = searchNode(list->head, dataToSearch);

            if (node)
                std::cout << "Node was found -> " << node << "\n";
            else
                std::cout << "Node wasn't found\n";
        }
        else if (line == "push back") {
            BookData data;
            ListKnowledgeArea* newList = new ListKnowledgeArea;
            std::string line;
            std::cout << "New book data: "; std::cin >> data;
            std::cout << "New knowledge areas: "; 
       
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
        else if (line == "create knowledge area") {
            listKnowledgeArea = createListKnowledgeArea(list->head);
            printFromLeftToRight<NodeKnowledgeArea>(listKnowledgeArea->head);
        }
        else if (line == "remove") {

        }
        else if (line == "move") {
            int id;
            std::cout << "Id = "; std::cin >> id;
            moveNodes(*list, id);
            printFromLeftToRight(list->head);
        }
        std::cout << "\n";
        std::getline(std::cin, line);
    }
    
    delete list;
    delete listKnowledgeArea;
    //for (int i = 0; i < size; ++i)
    //    delete[] listKnowledgeAreaForList[i];
    //delete[] listKnowledgeAreaForList;

    return 0;
}
