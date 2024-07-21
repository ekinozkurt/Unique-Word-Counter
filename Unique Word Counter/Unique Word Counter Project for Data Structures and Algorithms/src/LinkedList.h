
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <string>

// WordCount class holds word and count
struct WordCount {
public:
	std::string word;
	int count;

	WordCount() : word(""), count(0)
	{
	}

	WordCount(const std::string& word, int count) : word(word), count(count)
	{
	}
};

// Linkedlist node
struct Node {
public:
	WordCount wordCount;
	struct Node* next;
	struct Node* prev;

	Node(const WordCount& wordCount) : wordCount(wordCount), next(NULL), prev(NULL)
	{
	}
};

// Linkedlist class
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	// Add to end of the linked list
	void add(WordCount& wordCount);
	// Remove element from the beginning of the linked list 
	void remove();
	// If a string exist in the linked list
	bool isExist(const std::string& word);
	// Number of elements in the linked list
	int count();

private:
	// Head of the linkedlist
	Node* head;
	// Tail of the linked list
	Node* tail;
	// Size of the linked list
	int size;
};

#endif
