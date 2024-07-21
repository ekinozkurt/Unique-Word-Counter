
#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "LinkedList.h"

// Hash table size
#define HASHTABLE_SIZE		32783

// Top 10 most frequently used
#define MAX_COUNT	10

// Hash table class
class HashTable {
public:
	// Add word count to the hash table
	void add(WordCount& wordCount);
	// Check if word exist in the hash table
	bool isExist(const std::string&word);
	// Print top 10 most frequently used word
	void printMostUsed();

private:
	// Create hash value of the word
	unsigned hash(const char* s);
	// Update most frequently used words array
	int updateMostUsed(WordCount& wordCount);

private:
	// Hash table holds words with counts
	LinkedList table[HASHTABLE_SIZE];
	// Holds top 10 mostly used words
	WordCount mostUsedWordCounts[MAX_COUNT];
};

#endif
