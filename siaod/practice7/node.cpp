// node.cpp

#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>


std::ostream& operator<< (std::ostream& out, const BookData& data) {
	out << data.number;
	return out;
}

std::istream& operator>> (std::istream& in, BookData& data) {
	in >> data.number >> data.author >> data.name >> data.year;
	return in;
}

BookData::BookData() {
	knowledgeArea = new ListKnowledgeArea;
}

List::~List() {
	while (head) {
		last = head->next;
		delete head->data.knowledgeArea;
		delete head;
		head = last;
	}
}

Node::Node(Node* next, Node* prev, BookData data) {
	this->next = next;
	this->prev = prev;
	this->data = data;
};

NodeKnowledgeArea::NodeKnowledgeArea(
	NodeKnowledgeArea* next, NodeKnowledgeArea* prev, std::string data
) {
	this->next = next;
	this->prev = prev;
	this->data = data;
};

ListKnowledgeArea::~ListKnowledgeArea() {
	while (head) {
		last = head->next;
		delete head;
		head = last;
	}
}

Node* searchNode(Node* head, int id) {
	for (Node* temp = head; temp; temp = temp->next) {
		if (temp->data.number == id)
			return temp;
	}
	return nullptr;
}

ListKnowledgeArea* createListKnowledgeArea(Node* head) {
	ListKnowledgeArea* listArea = new ListKnowledgeArea;
	std::vector<std::string> names;

	for (Node* temp = head; temp; temp = temp->next) {
		for (
			NodeKnowledgeArea* tempArea = temp->data.knowledgeArea->head;
			tempArea;
			tempArea = tempArea->next
		) {
			if (std::find(names.begin(), names.end(), tempArea->data) == names.end()) {
				pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
					listArea, tempArea->data
				);
				names.push_back(tempArea->data);
			}
		}
	}
	return listArea;
}

void deleteNode(List*& list, Node*& node) {
	if (!node->prev && !node->next) {
		list->head = list->last = nullptr;
	}
	else if (!node->prev) {
		node->next->prev = nullptr;
		list->head = node->next;
	}
	else if (!node->next) {
		node->prev->next = nullptr;
		list->last = node->prev;
	}
	else {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	delete node->data.knowledgeArea;
	delete node;
	node = nullptr;
}

void removeNodes(List*& list, std::string author, int year) {
	Node* current;
	for (Node* temp = list->head; temp; temp = current) {
		current = temp->next;
		if (temp->data.author == author && temp->data.year > year)
			deleteNode(list, temp);
	}
}

void moveNodes(List*& list, int id) {
	for (Node* current = list->head; current; current = current->next) {
		if (current->data.number == id) {
			Node* currentPrev = current->prev;
			currentPrev->next = nullptr;
			current->prev = nullptr;

			list->last->next = list->head;
			list->head->prev = list->last;
			list->head = current;
			list->last = currentPrev;
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

void fillWithKnoweldgeAreas(Node*& head) {
	int ind = 0;
	for (Node* temp = head; temp; temp = temp->next) {
		temp->data.knowledgeArea = new ListKnowledgeArea;
		std::string line;
		std::cout << ind++ << ": ";
		while ((std::cin >> line) && line != "0") {
			pushBack<NodeKnowledgeArea, ListKnowledgeArea, std::string>(
				temp->data.knowledgeArea, line
				);
		}
	}
}

void printKnowledgeAreasFromLeftToRight(Node*& head) {
	int ind = 0;
	for (Node* temp = head; temp; temp = temp->next) {
		std::cout << ind++ << " ";
		if (temp->data.knowledgeArea->head)
			printFromLeftToRight(temp->data.knowledgeArea->head);
		else
			std::cout << "empty\n";
	}
}

void printKnowledgeAreasFromRightToLeft(Node*& last) {
	int ind = 0;
	for (Node* temp = last; temp; temp = temp->prev) {
		std::cout << ind++ << " ";
		if (temp->data.knowledgeArea->last)
			printFromRightToLeft(temp->data.knowledgeArea->last);
		else
			std::cout << "empty\n";
	}
}
