#include "a3.h"


int getIdx(char ch) {
    return ch -'a';
}

Trie::Trie(){}

Trie::Trie(const std::string wordList[],int sz) {

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

void Trie::searchHelper(const std::string& prefix, std::string resultList[], TrieNode* node, int& count) const {
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

Trie::~Trie() {
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
    return tn;
}
