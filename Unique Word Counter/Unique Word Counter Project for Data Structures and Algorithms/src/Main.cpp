
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>

#include "HashTable.h"

// Read files and add them to hash table and find top 10 most frequent words not exist in the stopwords file
void process(const char* dataFileName, const char* stopwordsFileName)
{
	// Hash table holds stop words
	HashTable* stopwordsTable = new HashTable();

	// Read stop words file
	std::ifstream stopwordsfile(stopwordsFileName);

	if (stopwordsfile.is_open()) {
		std::string line;

		while (std::getline(stopwordsfile, line)) {
			line[strcspn(line.c_str(), "\r\n")] = 0;

			WordCount wordCount(line, 1);
			stopwordsTable->add(wordCount);
		}

		stopwordsfile.close();
	}

	// Hash table holds words in the publications except stop words
	HashTable* dataTable = new HashTable();

	std::ifstream datafile(dataFileName);

	if (datafile.is_open()) {
		std::string line;

		// Read file line by line
		while (std::getline(datafile, line)) {
			line[strcspn(line.c_str(), "\r\n")] = 0;

			size_t len = line.length();
			std::size_t prev = 0, pos;

			// Parse word / count after unigramCount keyword
			prev = line.find("\"unigramCount\":{");

			if (prev == std::string::npos)
				continue;

			prev += 16;
			bool isWord = false;

			WordCount wordCount;

			for (size_t i = prev; i < len; i++) {
				if (!isWord) {
					if (line[i] == '\"') {
						prev = i+1;
						isWord = true;
					}
					else {
						if (line[i] == ':') {
							prev = i+1;
						}
						else if (line[i] == ',' || line[i] == '}') {
							pos = i;
							
							wordCount.count = std::stoi(line.substr(prev, pos - prev));
							
							if (!wordCount.word.empty()) {
								// Check if exist in the stop words
								if (!stopwordsTable->isExist(wordCount.word)) {
									dataTable->add(wordCount);
								}
							}

							wordCount.word = "";
							wordCount.count = 0;
						}
					}
				}
				else {
					if (line[i] == '\"') {
						int count = 0;

						for (size_t j = i - 1; j >= 0; --j) {
							if (line[j] == '\\')
								count++;
							else
								break;
						}

						if (count % 2 == 0) {
							pos = i;
							isWord = false;

							wordCount.word = line.substr(prev, pos - prev);

							// Convert word to lower case
							for (size_t j = 0; j < wordCount.word.length(); j++) {
								wordCount.word[j] = std::tolower(wordCount.word[j]);
							}
						}
					}

				}
			}
		}

		datafile.close();
	}

	// Print most frequently used words
	dataTable->printMostUsed();

	// Delete hash tables created
	delete dataTable;
	delete stopwordsTable;
}

// Main method
int main(int argc, char *argv[])
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	process("PublicationsDataSet.txt", "stopwords.txt");

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	// Print elapsed time
	std::cout << "Elapsed time : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0 << " seconds" << std::endl;

	return 0;
}
