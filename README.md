# Trie Tree Data Structure and Algorithms

# Cached Doubly Linked List

## Outcomes

In this assignment I implemented:
- a Trie data structure
- algorithms for adding, complete word search, and auto complete word search

## Credits
In collaboration with [Jacky Dai](https://www.linkedin.com/in/jacky-dai-29620022b/)

# Reflection

The data structures I will discuss in the reflection are Binary Tree and Hash Tables.

## How efficient is the creation Trie vs your chosen data structures.

Creating a trie is most likely less efficient than if we implemented the same dictionary functionality with something like a Hash Table, or even 
a Binary Tree since for every node of the trie, we must use children ranging from index 0 ('a') to index 25 ('z'). I believe this is only applicable for average cases where the dictionary is not infinitely large, since a Hash Table will insert with BigO of O(1), and a Binary Tree will insert at a BigO of log(n). A Hash Table however, could potentially result in an O(n) time complexity, while a Binary Tree could result in a O(n^2) complexity if the size of the dictionary is extremely large, in which case the Trie will likely be the better option.

## How good will that data structure be at the main look up tasks of a Trie(search and begins_with).

Both a Hash Table and a Binary Tree will most likely be much more efficient at a simple boolean search algorithm, where the exact match is needed, since a Hash Table will return key-value pairs at O(1) time complexity, and a Binary Tree will return a find at O(logN) time complexity. However, I don't think either of these structures will be able to efficiently perform the begins_with function, because it would require the traversal of both structures repeatedly until every possible letter combination is found.

## How can each of the chosen data structures support the two look up tasks (can you use the exist functionality or do you need to do something extra to what is typically returned?)

For the search functionality, hash tables will be able to handle the task relatively simply since the hashing and collision avoidance functions will allow the lookup of an exact word by either a binary search for the BT or by finding the hash index for the HT. As mentioned above, in order for either of these structures to perform the begins_with task, the entire structure will have to be read multiple times, to theoretically match all possibilities. Furthermore, when referring to Hash Tables, due to the hash function, and the collision handling, it is likely that a resulting autocomplete list would not be ordered alphabetically as we have done in our Trie structure. 


