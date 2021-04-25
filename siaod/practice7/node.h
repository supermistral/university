// node.h

#pragma once
#include <string>
#include <iostream>

struct ListKnowledgeArea;

struct BookData {
	int number, year;
	std::string author, name;
	ListKnowledgeArea* knowledgeArea;

	BookData();
};

template <class T1, class T2>
struct NodeBase {
	T1* next;
	T1* prev;
	T2 data;
};

struct Node
	: NodeBase<Node, BookData> {

	Node(Node*, Node*, BookData);
};

struct NodeKnowledgeArea
	: NodeBase<NodeKnowledgeArea, std::string> {

	NodeKnowledgeArea(NodeKnowledgeArea*, NodeKnowledgeArea*, std::string);
};

template <class T>
struct ListBase {
	T* head = nullptr;
	T* last = nullptr;
};

struct List
	: ListBase<Node> {

	~List();
};

struct ListKnowledgeArea
	: ListBase<NodeKnowledgeArea> {

	~ListKnowledgeArea();
};

std::ostream& operator<< (std::ostream&, const BookData&);
std::istream& operator>> (std::istream&, BookData&);

Node* searchNode(Node*, int);
ListKnowledgeArea* createListKnowledgeArea(Node*);
void removeNodes(List*&, std::string, int);
void moveNodes(List*&, int);
void deleteNode(List*&, Node*&);
List* createList(int&);
void fillWithKnoweldgeAreas(Node*&);
void printKnowledgeAreasFromLeftToRight(Node*&);
void printKnowledgeAreasFromRightToLeft(Node*&);

template <class T = Node>
void printFromLeftToRight(T* head) {
	std::cout << "List: " << head->data;
	for (T* temp = head->next; temp; temp = temp->next)
		std::cout << " <-> " << temp->data;
	std::cout << "\n";
}

template <class T = Node>
void printFromRightToLeft(T* last) {
	std::cout << "List: " << last->data;
	for (T* temp = last->prev; temp; temp = temp->prev)
		std::cout << " <-> " << temp->data;
	std::cout << "\n";
}

template <class T1 = Node, class T2 = List, class T3 = BookData>
void pushBack(T2*& list, T3 data) {
	T1* newNode = new T1(nullptr, list->last, data);
	if (!list->last)
		list->head = newNode;
	else
		list->last->next = newNode;
	list->last = newNode;
}
