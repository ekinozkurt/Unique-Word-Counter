
#include "LinkedList.h"

#include <iostream>

// Constructor
LinkedList::LinkedList()
{
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

// Destructor
LinkedList::~LinkedList()
{
	while (this->head != NULL)
		remove();
}

// Add to end of the linked list
void LinkedList::add(WordCount& wordCount)
{
	Node* node = this->head;

	while (node != NULL) {
		if (wordCount.word == node->wordCount.word) {
			node->wordCount.count += wordCount.count;
			wordCount.count = node->wordCount.count;
			return;
		}

		node = node->next;
	}

	node = new Node(wordCount);

	if (node == NULL)
		return;

	if (this->head == NULL) {
		this->head = node;
		this->tail = node;
	}
	else {
		this->tail->next = node;
		node->prev = this->tail;
		this->tail = node;
	}

	this->size++;
}

// Remove element from the beginning of the linked list 
void LinkedList::remove()
{
	Node* node;

	if (this->head == NULL) {
		return;
	}
	else if (this->head == this->tail) {
		node = this->head;

		delete node;

		this->head = NULL;
		this->tail = NULL;
	}
	else {
		node = this->head;

		node = this->head->next;
		delete this->head;

		this->head = node;
		node->prev = NULL;
	}

	this->size--;
}

// If a string exist in the linked list
bool LinkedList::isExist(const std::string& word)
{
	Node* node = this->head;

	while (node != NULL) {
		if (word == node->wordCount.word) {
			return true;
		}

		node = node->next;
	}

	return false;
}

// Number of elements in the linked list
int LinkedList::count()
{
	return size;
}
