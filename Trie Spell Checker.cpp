// Trie Spell Checker.cpp : Defines the entry point for the application.
//
#pragma once
#include "Trie Spell Checker.h"
#include "Instrumentor.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
// #define NDEBUG
#include <cassert>
#include <chrono>

using namespace std;


class Timer
{
public:
	
	long long duration = 0;

	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		SetDuration();

		double ms = duration * 0.01;
		//std::cout << duration << "us ("<< ms << "ms)" << endl;		

	}

	void SetDuration()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		duration = end - start;
	}

	long long GetDuration()
	{
		SetDuration();
		return duration*0.01;
	}

private:
	std::chrono::time_point< std::chrono::high_resolution_clock> m_StartTimepoint;
};

/// <summary>
/// Node for each leaf in tree
/// </summary>
struct TrieNode
{
	std::unordered_map<char, TrieNode*> children;
	bool IsWord = false;
};


/// <summary>
/// Generates the root node of the Trie
/// </summary>
/// <returns>Pointer to root node</returns>
TrieNode* GenerateNode()
{
	struct TrieNode *tNode = new TrieNode();
	tNode->IsWord = false;
	return tNode;
}

/// <summary>
/// Insert a word into the Trie
/// </summary>
/// <param name=""></param>
void InsertWord(TrieNode *root, const char word[])
{
	TrieNode* currentNode = root;

	for (int i = 0; i < strlen(word); i++)
	{
		// If first Letter is not in trie
		if (currentNode->children.count(word[i]) == 0)
		{
			// Add new leaf to root with said letter
			currentNode->children[word[i]] = GenerateNode();
			currentNode = currentNode->children[word[i]];

			// If end of word, mark as end
			if (i == strlen(word)-1)
			{
				currentNode->IsWord = true;
			}
		}
		// Set pointer to the next node
		else
		{
			currentNode = currentNode->children[word[i]];
		}
	}
	currentNode = NULL;
}



bool Search(TrieNode* root, const char word[])
{
	TrieNode* currentNode = root;
	for (int i = 0; i < std::strlen(word); i++)
	{
		for (std::pair<char, TrieNode*> el : currentNode->children)
		{			
			if (word[i] == el.first)
			{
				if (i == (std::strlen(word) - 1) && currentNode->children[el.first]->IsWord)
				{
					return true;
				}				
				currentNode = currentNode->children[el.first];
			}
		}
	}
	return false;
}


void PrintWord(TrieNode* root, const char word[])
{
	TrieNode* currentNode = root;

	for (int i = 0; i < strlen(word); i++)
	{		
		for (const std::pair<char, TrieNode*>& el : currentNode->children)
		{
			if (word[i] == el.first)
			{
				std::cout << el.first;
				currentNode = currentNode->children[el.first];
			}
		}
	}
}


std::vector<string> GetAllWords(std::string filePath)
{
	string word;
	std::vector<string> words;

	ifstream WordFile(filePath);

	assert(WordFile.is_open());
	if (WordFile.is_open())
	{
		while (std::getline(WordFile, word))
		{
			words.push_back(word);
		}
		WordFile.close();
	}

	return words;
}


int main()
{
	const int length = 5;
	// File Read Method
	long long timerCount[length];
	for (int count = 0; count < length; count++)
	{
		// Insert Words as they're read from the file
		{
			Timer time;

			std::string filePath = "C:/codeProjects/tree/Trie Spell Checker/AllWords.txt";
			std::string word;
			TrieNode* root = GenerateNode();

			ifstream WordFile(filePath);

			assert(WordFile.is_open());

			if (WordFile.is_open())
			{
				// For every word, insert it into the tree
				while (std::getline(WordFile, word))
				{
					InsertWord(root, word.data());
				}
				WordFile.close();
			}
			timerCount[count] = time.GetDuration();
		}
	}
	long long meanTimeOpenFileMethod = 0;
	for(auto & a : timerCount)
	{
		meanTimeOpenFileMethod += a;
	}
	meanTimeOpenFileMethod = meanTimeOpenFileMethod / length;
	cout << "File Read Mean Time: " << meanTimeOpenFileMethod << endl;

	// Vector Method	
	for (int count = 0; count < length; count++)
	{
		// Read words into vector and then insert them
		{
			Timer timer;
			std::vector<string> Words = GetAllWords("C:/codeProjects/tree/Trie Spell Checker/AllWords.txt");
			TrieNode* root = GenerateNode();

			for (auto& a : Words)
			{
				InsertWord(root, a.data());
			}
			timerCount[count] = timer.GetDuration();
		}
	}
	long long meanTimeVectorMethod = 0;
	for (auto& a : timerCount)
	{
		meanTimeVectorMethod += a;
	}
	meanTimeVectorMethod = meanTimeVectorMethod / length;
	cout << "Vector Mean Time: " << meanTimeVectorMethod << endl;
	
	// Loop to run user imput tests
	while (true)
	{
		std::cout << "Enter a word" << endl;
		string newWord;
		cin >> newWord;
		
		// Convert user's word to lower case
		for (int i = 0; i < newWord.length(); i++)
		{
			if (newWord[i] >= 65 && newWord[i] <= 90)
			{
				newWord[i] += 32;
			}
		}
	
		const char* cStr = newWord.c_str();

		//if (!Search(root, cStr))
		//{
		//	std::cout << "Not a Word" << endl;
		//}
		//else 
		//{
		//	std::cout << "Good Spelling" << endl;
		//}
	}

	std::cout << "ran" << endl;
	return 0;
}


