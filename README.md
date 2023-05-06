# COMP290 Trie Spell Checker

This project use's an implementation of a Trie data structure to contain and search for every word in the entire english language. This approach uses several optimizations to handle creation, insertion and search.

## Spell Check Design

### Trie

A **Tree** is a hierarchical data structure comprised of nodes containing infomation. A **Trie** is a form of tree used to find keys within a set. To write a spell checker there two large requirements
- It must be able to contain lots of data, as it needs to contain all the words in the English language
- It must a fast Big(0), as to be able to search the entire dictionary

Unlike other Tree structures, such as a binary tree or AVL tree, a trie does not need any balancing actions performed upon it to keep its efficiency. Keys, as they are just letters, are unordered and are only dependent on the node above it, but independent from the leafs on the same level. Each node contains a boolean value, indicating whether the node is at the end of a word, and an unordered map, containing the letter as its key and a pointer to the next node. However, many implementations also us a standard map. 

### Map VS Unordered Map

Both types of maps are contained in the C++ standard library. A map is a "sorted associative container that contains key-value pairs with unique keys". They're implemented using Red-black trees, a self-balancing form of binary tree. An unordered-map is a "associative container that contains key-value pairs with unique keys", implemented using a hash-table. Hash-tables have a very fast search time, since once the hash is commutated, the exact location is know, only when there are duplicated key, are they keys placed into bucket, that then have to be searched linearly in O(1).

I choice to use an unordered-map instead of a standard map for two main reasons.
-  Its constant time search. Insertion speed is not critical in a spell checker, as the user will only interact with the Search complexity when spelling a word. Therefore, this optimization greatly improves the user's experience.
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

## Post Design Optimization Decisions    

## Next Steps