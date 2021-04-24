#pragma once
#include <string>
#include <iostream>


template <class T1, class T2>
struct NodeBase {
	T1* next;
	T1* prev;
	T2 data;
};

template <class T>
struct ListBase {
	T* head = nullptr;
	T* last = nullptr;
};

struct Node 
	: NodeBase<Node, BookData> {

	Node(Node* next, Node* prev, BookData data) {
		this->next = next;
		this->prev = prev;
		this->data = data;
	};
};

struct NodeKnowledgeArea 
	: NodeBase<NodeKnowledgeArea, std::string> {

	NodeKnowledgeArea(
		NodeKnowledgeArea* next, NodeKnowledgeArea* prev, std::string data
	) {
		this->next = next;
		this->prev = prev;
		this->data = data;
	};
};

struct List
	: ListBase<Node> {
	
	~List() {
		deleteList<List>(*this);
	};
};

struct ListKnowledgeArea
	: ListBase<NodeKnowledgeArea> {

	~ListKnowledgeArea() {
		deleteList<ListKnowledgeArea>(*this);
	};
};

struct BookData {
	int number, year;
	std::string author, name;
	ListKnowledgeArea knowledgeArea;
};


std::ostream& operator<< (std::ostream& out, const BookData& data) {
	out << data.number;
}

std::istream& operator>> (std::istream& in, BookData& data) {
	in >> data.number >> data.author >> data.name >> data.year;
}

bool operator== (const BookData& data1, const BookData& data2) {
	return data1.author == data2.author && data1.name == data2.name
		&& data1.year == data1.year;
}

template <class T = Node>
void printFromLeftToRight(T*);

template <class T = Node>
void printFromRightToLeft(T*);

Node* searchNode(Node*, BookData);

template <class T1 = Node, class T2 = List, class T3 = BookData>
void pushBack(T2&, T3);

template<class T1>
void deleteList(T1&);

ListKnowledgeArea createListKnoweldgeArea(Node*);
void removeNodes(Node*, std::string, std::string);
void moveNodes(List&, int);
void deleteNode(Node*&);
List createList(int&);
