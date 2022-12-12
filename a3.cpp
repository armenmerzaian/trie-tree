#include "a3.h"


int getIdx(char ch) {
    return ch -'a';
}

Trie::Trie(){}

// Overloaded constructor
// The constructor is passed an array of words and the size of the array.
// It initializes the Trie to hold all the words in wordlist by calling a function addWord
// The Trie contains a root -> array of TrieNodes for each letter of the alphabet
Trie::Trie(const std::string wordList[],int sz) {

    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int j = 0;
    for (auto &i : root)
    {
        i = addTrieNode(alphabet[j++], *root);
    }

    for(int i = 0; i < sz; i++){
        addWord(wordList[i]);
    }
}


// function addWord take a string reference, finds its starting place in the root of the Trie
// then iteratively inserts each letter of the word as its own TrieNode
// nesting down and adding each consecutive letter as a child of the previous letter in the word
// when the word is complete, it flags the end of a word in that last letter's TrieNode
// using the _terminal flag
void Trie::addWord(const std::string& newWord) {
    int index = getIdx(newWord[0]);
    TrieNode* temp = this->root[index];
    if(!temp->_ltr){
        temp = addTrieNode(newWord[0], temp);
    }
    for (int i=1; i < newWord.length(); i++) {
        int idx = getIdx(newWord[i]);
        if (temp->_children[idx] == nullptr) {
            temp->_children[idx] = addTrieNode(newWord[i], temp);
        }
        temp = temp->_children[idx];
    }
    temp->_terminal = true;
}

//function lookup returns true if word is in the Trie, false otherwise.
// finds its starting point in the root of the Trie
// then nests down matching each letter from the word to
// one of the children in the TrieNode. If nesting fails, false is returned
// signaling that the word does not exist
bool Trie::lookup(const std::string& word) const {
    int index = getIdx(word[0]);
    TrieNode* temp = this->root[index];
    if(!temp->_ltr){
        return false;
    }
    for(int i=1; i < word.size(); i++)
    {
        int idx = getIdx(word[i]);
        if (temp->_children[idx] == nullptr) {
            return false;
        }
        temp = temp->_children[idx];
    }
    if (temp->_terminal){
        return true;
    }
    return false;
}

// recursive helper function for the beginsWith function returns void
// returns references to the resultList and the count on return
// recursively nests into each possible TrieNode child until it reaches
// a _terminal == true flag indicating that a word is found.
// when a word is found, it adds it to the resultList array of strings
void Trie::searchHelper(const string& prefix, string resultList[], TrieNode* node, int& count) const {
    string word = prefix;
    for (auto & i : node->_children) {
        if (i != nullptr) {
            word += i->_ltr;
            if (i->_terminal) {
                resultList[count++] = word;
            }
            searchHelper(word, resultList, i, count);
            word.pop_back();
        }

    }
}

// function is passed a prefix. It passes back an alphabetical list of all words in the Trie that begin
// with the given prefix through a reference to resultList.
// Function returns number of words in the result list.
// After iteratively searching for and finding the nested TrieNode matching
// the end letter of the prefix string, calls on searchHelper to recursively
// find every possible outcome.
int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const {
    int index = getIdx(prefix[0]);
    TrieNode* temp = this->root[index];
    int count = 0;
    const string& word = prefix;

    if (!word.empty()) {
        for (int i = 1; i < prefix.length(); i++) {
            int idx = getIdx(prefix[i]);
            temp = temp->_children[idx];
        }
        if (temp->_terminal) {
            resultList[count++] = word;
        }
        searchHelper(word, resultList, temp, count);
    }
    return count;
}

// recursive function searches each child of a TrieNode
// If the children are already empty, returns void,
// If the children are not empty recursively deletes the TrieNodes
void Trie::remove(TrieNode *tn) {
    if(tn == nullptr){
        return;
    }
    bool hasChildren = false;
    for (auto &i: tn->_children) {
        if (i) {
            hasChildren = true;
        }
    }
    if (!hasChildren) {
        delete tn;
        return;
    }
    for (auto &i: tn->_children) {
        remove(i);
    }
}

// destructor loops through each TrieNode child of the
// Trie through the root and calls the recursive remove function
// to determine if a child node needs to be released from memory
Trie::~Trie() {
    for (auto & i : root){
        remove(i);
    }
}

//function is passed a character letter, along with a reference to a parent TrieNode
//dynamically creates a TrieNode instance as a child of the parent TrieNode
//sets empty properties for the child
// returns a pointer to the newly created node
Trie::TrieNode *Trie::addTrieNode(const char ltr, TrieNode* parent) {
    auto* tn = new TrieNode(parent);
    for (auto& i : tn->_children) {
        i = nullptr;
    }
    tn->_terminal = false;
    tn->_ltr = ltr;
    return tn;
}
