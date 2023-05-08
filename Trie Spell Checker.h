// Trie Spell Checker.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <string>

// TODO: Reference additional headers your program requires here.
using namespace std;

struct TrieNode;

void InsertWord(TrieNode* root, const char word[]);

bool Search(TrieNode* root, const char word[]);

void PrintWord(TrieNode* root, const char word[]);
