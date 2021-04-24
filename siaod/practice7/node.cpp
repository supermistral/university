#include "node.h"
#include <iostream>
#include <set>

template <class T>
void printFromLeftToRight(T* head) {
	for (T* temp = head; temp; temp = temp->next)
		std::cout << temp->data << " ";
}

template <class T>
void printFromRightToLeft(T* last) {
	for (T* temp = last; temp; temp = temp->prev)
		std::cout << temp->data << " ";
}

Node* searchNode(Node* head, BookData data) {
	for (Node* temp = head; temp; temp = temp->next) {
		if (temp->data == data)
			return temp;
	}
	return nullptr;
}

template <class T1, class T2, class T3>
void pushBack(T2& list, T3 data) {
	T1* newNode = new T1(nullptr, list.last, data);
	if (!list.head) {
		list.head = newNode;
		return;
	}
	list.last->next = newNode;
	list.last = newNode;
}

template<class T1>
void deleteList(T1& list) {
	while (list.head) {
		list.last = list.head->next;
		delete list.head;
		list.head = list.last;
	}
}

ListKnowledgeArea createListKnowledgeArea(Node* head) {
	ListKnowledgeArea listArea;
	std::set<std::string> names;

	for (Node* temp = head; temp; temp = temp->next) {
		for (
			NodeKnowledgeArea* headArea = temp->data.knowledgeArea.head;
			headArea;
			headArea = headArea->next
		) {
			names.insert(headArea->data);
			if (names.find(headArea->data) != names.end())
				pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(listArea, headArea->data);
		}
	}
	return listArea;
}

void deleteNode(Node*& node) {
	if (!node->prev && !node->next) {
	}
	else if (!node->prev) {
		node->next->prev = nullptr;
	}
	else if (!node->next) {
		node->prev->next = nullptr;
	}
	else {
		node->next->prev = nullptr;
		node->prev->next = nullptr;
	}
	delete node;
}

void removeNodes(Node*& head, std::string author, int year) {
	for (Node* temp = head; temp; temp = temp->next) {
		if (temp->data.author == author && temp->data.year > year)
			deleteNode(temp);
	}
}

void moveNodes(List& list, int id) {
	for (Node* temp = list.head; temp; temp = temp->next) {
		if (temp->data.number == id) {
			Node* tempPrev = temp->prev;
			tempPrev->next = nullptr;
			temp->prev = nullptr;
			list.last->next = list.head;
			list.head->prev = list.last;
			list.head = temp;
			list.last = tempPrev;
			return;
		}
	}
}

List createList(int& size) {
	BookData data;
	std::cout << "List size = "; std::cin >> size;
	for (int i = 0; i < size; ++i) {
		std::cin >> data;
	}
}
