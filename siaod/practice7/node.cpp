#include "node.h"
#include <set>
#include <iostream>


std::ostream& operator<< (std::ostream& out, const BookData& data) {
	out << data.number;
	return out;
}

std::istream& operator>> (std::istream& in, BookData& data) {
	in >> data.number >> data.author >> data.name >> data.year;
	return in;
}

bool operator== (const BookData& data1, const BookData& data2) {
	return data1.author == data2.author && data1.name == data2.name
		&& data1.year == data1.year;
}


List::~List() {
	while (head) {
		last = head->next;
		delete head;
		head = last;
	}
}

ListKnowledgeArea::~ListKnowledgeArea() {
	while (head) {
		last = head->next;
		delete head;
		head = last;
	}
}

BookData::~BookData() {
	delete knowledgeArea;
}

Node* searchNode(Node* head, BookData data) {
	for (Node* temp = head; temp; temp = temp->next) {
		if (temp->data == data)
			return temp;
	}
	return nullptr;
}

ListKnowledgeArea* createListKnowledgeArea(Node* head) {
	ListKnowledgeArea* listArea = new ListKnowledgeArea;
	std::set<std::string> names;

	for (Node* temp = head; temp; temp = temp->next) {
		for (
			NodeKnowledgeArea* headArea = temp->data.knowledgeArea->head;
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
		node->next->prev = node->prev;
		node->prev->next = node->next;
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

List* createList(int& size) {
	BookData data;
	List* list = new List;
	std::cout << "List size = "; std::cin >> size;
	std::cout << "For every book: id author name year\n";
	for (int i = 0; i < size; ++i) {
		std::cin >> data;
		pushBack(list, data);
	}
	return list;
}
