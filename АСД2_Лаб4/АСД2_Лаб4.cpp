#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <map>
#include "Data.cpp"

using namespace std;

struct Node
{
    Data data;
    Node* left;
    Node* right;
};

struct BinarySearchTree
{
public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    Node* insert(Data& object)
    {
        root = insertIn(root, object);
        return root;
    }

    bool find(Data& object)
    {
        return findIn(root, object);
    } 

    Node* erase(Data& object)
    {
        return eraseIn(root, object);
    }

    int size()
    {
        return sizeIn(root);
    }

    void print()
    {
        return printIn(root);
    }

    int height()
    {
        return heightIn(root);
    }

    int findInRange(Data& min, Data& max)
    {
        int counter = 0;

        findInRangeIn(root, counter, min, max);
        
        return counter;
    }

    ~BinarySearchTree()
    {
        clear(root);

        delete root;
    }

private:
    Node* root;

    Node* newNode(Data& obj)
    {
        Node* newNode = new Node();

        newNode->data = obj;

        newNode->left = nullptr;

        newNode->right = nullptr;

        return newNode;
    }

    Node* minValue(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    Node* insertIn(Node* node, Data& object)
    {
        if (node == nullptr)
        {
            node = newNode(object);
        }
        else if (node->data > object)
        {
            node->left = insertIn(node->left, object);
        }
        else if (node->data < object)
        {
            node->right = insertIn(node->right, object);
        }
        else if (node->data == object)
        {
            node->data = object;
        }

        return node;
    }

    bool findIn(Node* node, Data& object)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->data == object)
        {
            return true;
        }

        if (node->data > object)
        {
            return findIn(node->left, object);
        }

        if (node->data < object)
        {
            return findIn(node->right, object);
        }
    }

    Node* eraseIn(Node* node, Data& object)
    {
        if (node == nullptr)
        {
            return node;
        }
        else if (node->data > object)
        {
            node->left = eraseIn(node->left, object);
        }
        else if (node->data < object)
        {
            node->right = eraseIn(node->right, object);
        }
        else if (node->data == object)
        {
            if(node->right == nullptr && node->left == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                Node* temp = node->right;

                delete node;

                node = temp;
            }
            else if (node->right == nullptr)
            {
                Node* temp = node->left;

                delete node;

                node = temp;
            }
            else
            {
                Node* temp = minValue(node->right);

                node->data = temp->data;

                node->right = eraseIn(node->right, temp->data);
            }
        }

        return node;
    }

    int sizeIn(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }

        return 1 + sizeIn(node->left) + sizeIn(node->right);
    }

    void printIn(Node* node)
    {
        if (node != nullptr)
        {
            printIn(node->left);

            cout << node->data.name << endl;

            printIn(node->right);
        }
    }

    int heightIn(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }

        return 1 + max(heightIn(node->left), heightIn(node->right));
    }

    void findInRangeIn(Node* node, int& counter, Data& min, Data& max)
    {
        if (node == nullptr)
        {
            return;
        }

        if ((node->data > min || node->data == min) && (node->data < max  || node->data == max))
        {
            counter++;
        }

        if (node->data < min)
        {
            return findInRangeIn(node->right, counter, min, max);
        }
        else if (node->data > max)
        {
            return findInRangeIn(node->left, counter, min, max);
        }
        else
        {
            findInRangeIn(node->left, counter, min, max);
            findInRangeIn(node->right, counter, min, max);
            return;
        }
    }

    void clear(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return;
        }

        clear(node->left);
        clear(node->right);
        return;
    }

    
};

long long generateRandLong()
{
    long long int result = 0;
    int numbersAmount = 10 + rand() % 6;

    for (int i = 0; i < numbersAmount; i++)
    {
        result += (1 + rand() % 9) * pow(10, i);
    }
    return result;
}

bool testBinarySearchTree()
{
    srand(time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Data> data(keysAmount);
    vector<Data> dataToInsert(iters);
    vector<Data> dataToErase(iters);
    vector<Data> dataToFind(iters);
    vector<pair<Data, Data>> dataToRangeQueries;
    for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[generateRandLong() % keysAmount];
        dataToErase[i] = data[generateRandLong() % keysAmount];
        dataToFind[i] = data[generateRandLong() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Data minData = Data();
        Data maxData = Data();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({ minData, maxData });
    }
    BinarySearchTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
        
    }
    //myTree.print();
    //cout << endl << endl;
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    //myTree.print();
    //cout << endl << endl;
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

    set<Data> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first,
            dataToRangeQueries[i].second);
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<
        optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount : " << myFoundAmount << endl;
        cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount
        << endl << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize <<
        ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " <<
        stlRangeFoundAmount << endl << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

struct TrieNode
{
    char value;

    map<char, TrieNode*> child;

    bool isEnd;

    TrieNode(char ch)
    {
        value = ch;

        isEnd = false;
    }
};

struct Trie
{
public:
    
    Trie()
    {
        root = new TrieNode(' ');
    }

    void insert(string word)
    {
        TrieNode* node = root;

        for (int i = 0; i < word.length(); i++)
        {
            if (node->child.find(word[i]) == node->child.end())
            {
                TrieNode* newNode = new TrieNode(word[i]);
                node->child[word[i]] = newNode;
            }

            node = node->child[word[i]];
        }

        node->isEnd = true;
    }

    vector<string> findByPrefix(string prefix)
    {
        vector<string> result;

        TrieNode* node = root;

        for (int i = 0; i < prefix.length(); i++)
        {
            if (node->child.find(prefix[i]) == node->child.end())
            {
                return result;
            }

            node = node->child[prefix[i]];
        }

        findWords(result, node, prefix);

        return result;
    }

    ~Trie()
    {
        clear(root);

        delete root;
    }

private:

    TrieNode* root;

    void findWords(vector<string>& arr, TrieNode* node, string& prefix)
    {
        if (node->isEnd)
        {
            arr.push_back(prefix);
        }

        for (auto it = node->child.begin(); it != node->child.end(); it++)
        {
            prefix.push_back(it->second->value);

            findWords(arr, it->second, prefix);

            prefix.pop_back();
        }
    }

    void clear(TrieNode* node)
    {
        if (node->child.size() == 0)
        {
            delete node;

            return;
        }

        for (auto it = node->child.begin(); it != node->child.end(); it++)
        {
            clear(it->second);
        }
    }

};

int main()
{
    testBinarySearchTree();

    cout << endl << endl;

    ifstream file("words_alpha.txt");

    Trie prefixTree;
    string line;

    clock_t start = clock();
    while (getline(file, line))
    {
        prefixTree.insert(line);
    }
    clock_t end = clock();
    float insertTime = (float(end - start)) / CLOCKS_PER_SEC;

    file.close();

    string prefix;

    cout << "Enter prefix: ";
    cin >> prefix;
    
    vector<string> res = prefixTree.findByPrefix(prefix);

    clock_t start1 = clock();
    if (res.size() == 0)
    {
        cout << "\nNo words with prefix '" << prefix << "' found." << endl;
    }
    else
    {
        cout << "\nFound words: " << endl;

        for (int i = 0; i < res.size(); i++)
        {
            cout << res[i] << endl;
        }
    }
    clock_t end1 = clock();
    float findTime = (float(end1 - start1)) / CLOCKS_PER_SEC;

    cout << "\nInsertTime: " << insertTime << ", FindTime: " << findTime << endl;
}
