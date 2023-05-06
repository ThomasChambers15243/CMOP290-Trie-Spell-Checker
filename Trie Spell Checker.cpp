// Trie Spell Checker.cpp : Defines the entry point for the application.
//
#pragma once
#include "Trie Spell Checker.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
// #define NDEBUG
#include <cassert>
using namespace std;

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
	std::vector<string> Words = GetAllWords("C:/codeProjects/tree/Trie Spell Checker/AllWords.txt");
	TrieNode* root = GenerateNode();

	for (auto& a : Words)
	{		
		InsertWord(root, a.data());
	}	
	
	// Loop to run user imput tests
	while (true)
	{
		std::cout << "Enter a word" << endl;
		string newWord;
		cin >> newWord;
		const char* cstr = newWord.c_str();

		if (!Search(root, cstr))
		{
			std::cout << "Not a Word" << endl;
		}
		else 
		{
			std::cout << "Good Spelling" << endl;
		}
	}
	//std::string word = "";
	//vector<std::string> words;
	//words = GetAllPossibleWordsFromNodeRoot(root, word, words);

	std::cout << "ran" << endl;
	return 0;
}


