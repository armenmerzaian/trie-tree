#include "a3.h"
#include <string>


int getIdx(char ch){
    return ch -'a';
}

Trie::Trie(){}

Trie::Trie(const std::string wordList[],int sz){

    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int j = 0;
    for (auto &i : root)
    {
        i = addTrieNode(alphabet[j++], *root);
    }

    for(int i = 0; i < sz; i++){
        string currWord = wordList[i];
        addWord(currWord);
    }
}



void Trie::addWord(const std::string& newWord){
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

bool Trie::lookup(const std::string& word) const{
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

//This function checks for how many words will start with a prefix and saves them in an array
// of strings that use the prefix. We will use two different functions to grab how many words
//have this prefix and we will call on a separate function to add each word to the resultList array
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
        searchHelper(word, resultList, count, temp);
    }
    return count;
}

//This function will check for each word that has the same prefix identified. We save the prefix and
//the current node into temporary variables so that we can modify them to grab each word. However once we
//reach the end of the word with the prefix, we will add it to the resultList and call the function (recursion)
//to check for any other words that go beyond the end of the word we orignally found. Once we save all the words
//found with the prefix, we will end this loop, returning back to the original function beginsWith
void Trie::searchHelper(const std::string& prefix, std::string resultList[], int& counter, TrieNode* tempNode) const
{
    string word = prefix;
    TrieNode* pfx = tempNode;
    for (int i = 0; i < 26; i++) {
        if (pfx->_children[i] != nullptr) {
            word += (i + 'a');
            if (pfx->_children[i]->_terminal) {
                resultList[counter++] = word;
            }
            pfx = pfx->_children[i];
            searchHelper(word, resultList, counter, pfx);
            word.pop_back();
            pfx = tempNode;
        }

    }
}

void Trie::remove(TrieNode *tn)
{
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

Trie::~Trie()
{
    for (auto & i : root){
        remove(i);
    }
}

Trie::TrieNode *Trie::addTrieNode(const char ltr, TrieNode* parent) {
    auto* tn = new TrieNode(parent);
    for (auto& i : tn->_children) {
        i = nullptr;
    }
    tn->_terminal = false;
    tn->_ltr = ltr;
    tn->_suggested = false;
    return tn;
}
