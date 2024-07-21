
#include "HashTable.h"

#include <iostream>

#define NUMA		54059
#define NUMB		76963
#define NUMC		37

// Add word count to the hash table
void HashTable::add(WordCount& wordCount)
{
	unsigned h = hash(wordCount.word.c_str());

	// Add to hash table
	table[h].add(wordCount);
	// Update most frequently used words array
	updateMostUsed(wordCount);
}

// Check if word exist in the hash table
bool HashTable::isExist(const std::string& word)
{
	unsigned h = hash(word.c_str());

	return table[h].isExist(word.c_str());
}

// Print top 10 most frequently used word
void HashTable::printMostUsed()
{
	for (int i = 0; i < MAX_COUNT; ++i) {
		std::cout << mostUsedWordCounts[i].word << " :\t" << mostUsedWordCounts[i].count << std::endl;
	}
}

// Create hash value of the word
unsigned HashTable::hash(const char* s)
{
	unsigned h = NUMC;

	while (*s) {
		h = (h * NUMA) ^ (s[0] * NUMB);
		s++;
	}

	return h % HASHTABLE_SIZE;
}

// Update most frequently used words array
int HashTable::updateMostUsed(WordCount& wordCount)
{
	int newIndex = -1;
	int oldIndex = -1;

	for (int i = MAX_COUNT - 1; i >= 0; --i) {
		if (wordCount.word == mostUsedWordCounts[i].word) {
			oldIndex = i;
			break;
		}
	}

	for (int i = MAX_COUNT - 1; i >= 0; --i) {
		if (wordCount.count <= mostUsedWordCounts[i].count) {
			break;
		}

		newIndex = i;
	}

	if (newIndex == -1)
		return newIndex;

	if (oldIndex == -1)
		oldIndex = MAX_COUNT - 1;

	for (int i = oldIndex - 1; i >= newIndex; --i) {
		mostUsedWordCounts[i + 1] = mostUsedWordCounts[i];
	}

	mostUsedWordCounts[newIndex] = wordCount;

	return newIndex;
}
