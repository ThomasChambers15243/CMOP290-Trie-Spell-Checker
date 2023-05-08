# COMP290 Trie Spell Checker

This project use's an implementation of a Trie data structure to contain and search for every word in the entire english language. This approach uses several optimizations to handle creation, insertion and search.

## Spell Check Design

### Trie

A **Tree** is a hierarchical data structure comprised of nodes containing infomation. A **Trie** is a form of tree used to find keys within a set. To write a spell checker there two large requirements
- It must be able to contain lots of data, as it needs to contain all the words in the English language
- It must a fast Big(0), as to be able to search the entire dictionary

Unlike other Tree structures, such as a binary tree or AVL tree, a trie does not need any balancing actions performed upon it to keep its efficiency. This is key to its speed, as hundreds of thousands of insertions are needed, constant balancing would greatly slow down the Trie generation. Keys, as they are just letters, are unordered and are only dependent on the node above it, but independent from the leafs on the same level. Each node contains a boolean value, indicating whether the node is at the end of a word, and an unordered map, containing the letter as its key and a pointer to the next node. However, many implementations also us a standard map. 

### Map VS Unordered Map

Both types of maps are contained in the C++ standard library. A map is a "sorted associative container that contains key-value pairs with unique keys". They're implemented using Red-black trees, a self-balancing form of binary tree. An unordered-map is a "associative container that contains key-value pairs with unique keys", implemented using a hash-table. Hash-tables have a very fast search time, since once the hash is commutated, the exact location is know, only when there are duplicated key, are they keys placed into bucket, that then have to be searched linearly in O(1).

I choice to use an unordered-map instead of a standard map for two main reasons.
-  Its constant time search. Insertion order is not important in a trie, so this greatly increase search speed.
- There is no need to balancing. Hundreds of thousands of words need to be inserted and stored. Constant balancing when inserting each letter of each word would greatly decreases generation time, when this isn't an issue with an unordered map.

|                    | **Map**                          | **Unordered_Map**            |
|--------------------|----------------------------------|------------------------------|
| **Structure**      | Ordered by Keys                  | Unordered, associative       |
| **Implementation** | Red-Black Tree                   | Hash Table                   |
| **Balance**        | O(1) Average O(log N) Worst Case | Not Needed                   |
| **Insertion**      | Log(n) + Rebalance               | O(1) Average O(N) Worst Case |
| **Search**         | Log(N)                           | O(1) Average O(N) Worst Case |
| **Deletion**       | Log(N) + Rebalance               | O(1) Average O(N) Worst Case |
| **Space**          | O(n)                             | O(n)                         |

## Methods for loading Words from .txt into the Trie

All words are stored in a text file of 370,105 words. My first solution to loading these into the trie was to first read all the words into a vector and then iterate through that vector, inserting each word into the tree. However, the problem with this is that the vector has to update its size every time its filled, which will happen thousands of times as the words are loading. This is an expensive process. 

An optimization to this is too use a linked list. After the vectors creation, its only accessed in a linear fashion. The benefits gained from using a vector, fast, indexed access, is never used. A linked list would allow easy iteration from start to end, the only access needed to the structure. When a new word is added, its just added as a new node, with its memory address being pointed to by the previous node. When loading the words into the Trie, once iteration is used throughout the list. This would increase loading speed as theres never a need to resize and allocate new memory to the list.

A better optimization is to avoid loading the words into anything but the Trie. When the file is opened, as each word is read, InsertWord(word) is called. This methods consistency improves performance times.
|Number of Iterations|Vector Method (milliseconds)|On File Read Method (milliseconds)|
|--------------------|-------------|-------------------|
|5|2481.9|2097.5|
|10|2664.1|2133.7|
|15|2823.9|2116.3|
|20|2808.3|2230.6|