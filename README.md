# Implementation-of-the-binary-search-tree-and-prefix-tree-data-structure
1 year of computer science. Algorithms and data structures, Lab 8

# Task (translated using ChatGPT):

1. Create a Data structure to store objects with characteristics according to the chosen task, choose criteria for comparing two objects, and overload necessary operators.  

2. Implement a binary search tree:  
2.1 Create a basic tree element Node containing data and pointers to two descendants - left and right. Optionally, add a pointer to the parent node if necessary.  
2.2 Create a BinarySearchTree structure with basic methods of an unbalanced binary search tree:  
insert(object) – add a new element to the tree (without duplicates)  
find(object) – check the presence of an element in the tree  
erase(object) – remove an element from the tree  
size() – find the number of elements in the tree  
2.3 Implement additional methods for working with the tree:  
print() – display all elements of the tree (in sorted order)  
height() – find the height of the tree  
findInRange(minObject, maxObject) – find all elements in the tree in the range [minObject, maxObject], return their count or a dynamic array (vector) with these elements.  

3. Conduct testing using the testBinarySearchTree() function below. Check the correctness and speed of operation, comparing it with the ready-made library solution STL set.  

4. Implement a prefix tree:  
4.1 Implement a trie for word autocompletion. Example execution:  
Input: > algorit  
Output: > algorithm, algorithmic, algorithmically, algorithms  
4.2 Create a basic tree element Node that will contain a hash table (unordered_map), where the key is a text character, the value is a pointer to the corresponding Node, and a boolean flag indicating whether this node is the end of a word. Instead of a hash table, you can use a static or dynamic array, or a balanced tree (map); explore the optimality of such options.  
4.3 Create a Trie structure and implement the basic methods of the trie:  
insert(word) – add a new word to the trie  
findByPrefix(prefix) – find words that start with the specified prefix    
4.4 Read all existing words from a file and build a trie with them. You can take the file with words here:
[Link to words file](https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt)  
4.5 Test the correctness of the trie's operation using different prefixes entered from the keyboard.
