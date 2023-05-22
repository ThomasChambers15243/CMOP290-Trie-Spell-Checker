// Trie Spell Checker.cpp : Defines the entry point for the application.

#pragma once
#include "Trie Spell Checker.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
// #define NDEBUG
#include <cassert>
#include <chrono>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

/// <summary>
/// Timer Class for measuring algorithm speed
/// </summary>
class Timer
{
public:
	

	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	/// <summary>
	/// Returns the duration of the timer in milliseconds
	/// </summary>
	/// <returns></returns>
	double GetDuration()
	{
		SetDuration();
		return duration*0.01;
	}

private:
	
	double duration = 0;
	
	std::chrono::time_point< std::chrono::high_resolution_clock> m_StartTimepoint;

	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		SetDuration();
		double ms = duration * 0.01;
		std::cout << "Duration: " << ms << " (ms)" << endl;
	}

	void SetDuration()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		duration = end - start;
	}
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


/// <summary>
/// Finds the given word in a Trie
/// </summary>
/// <param name="root">Start of the Trie</param>
/// <param name="word">Word to be found</param>
/// <returns>True if found, else false</returns>
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

/// <summary>
/// Prints out a word from its nodes in the Trie
/// </summary>
/// <param name="root">Start of the Trie</param>
/// <param name="word">Word to be printed</param>
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

int main()
{

	// Insert Words as they're read from the file
	//std::string filePath = "C:/codeProjects/tree/Trie Spell Checker/AllWords.txt";
	fs::path directoryPath = fs::current_path();
	string filePath = directoryPath.generic_string() + "/AllWords.txt";
	std::string word;

	// Creates the start of the Trie
	TrieNode* root = GenerateNode();

	ifstream WordFile(filePath);

	assert(WordFile.is_open());
	
	// For every word, insert it into the tree
	if (WordFile.is_open())
	{
		while (std::getline(WordFile, word))
		{
			// Inset word into a string, passing through each string as a char* array
			InsertWord(root, word.data());
		}
		WordFile.close();
	}
	// If file could not be opened, end program
	else 
	{
		cout << "File could not open" << endl;
		return 1;
	}
	

	// Takes user input and checks its spelling by searching the Trie
	while (true)
	{
		std::cout << "Enter a word" << endl;
		string newWord = "";
		cin >> newWord;
		
		// Convert user's word to lower case
		for (int i = 0; i < newWord.length(); i++)
		{
			if (newWord[i] >= 65 && newWord[i] <= 90)
			{
				newWord[i] += 32;
			}
		}

		// Find word and outputs accordingly
		if (!Search(root, newWord.data()))
		{
			std::cout << "Not a Word" << endl;
			std::string userAnswer = "";
			// Give the user the option to add their word
			cout << "Add Word? (y/n)" << endl;
			cin >> userAnswer;
			if (userAnswer == "y")
			{
				InsertWord(root, newWord.data());
				if (Search(root, newWord.data()))
				{
					cout << "Word added successfully" << endl;
				}
				else
				{
					cout << "Something went wrong :(" << endl;
				}
			}
		}
		else
		{
			std::cout << "Good Spelling" << endl;
		}
	}
	
	return 0;
}