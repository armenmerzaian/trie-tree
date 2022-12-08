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
        i = addTrieNode(alphabet[j], *root);
        j++;
    }

    for(int i = 0; i < sz; i++){
        string currWord = wordList[i];
        int index = getIdx(currWord[0]);
        TrieNode* temp = this->root[index];
        temp->_ltr = currWord[0];
        for (int j=1; j < currWord.length(); j++) {
            int idx = getIdx(currWord[j]);
            if (temp->_children[idx] == nullptr) {
                temp->_children[idx] = addTrieNode(currWord[j], temp);
            }
            temp = temp->_children[idx];
        }
        temp->_terminal = true;
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
    // Searches for word in the Trie
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

int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const{
    int index = getIdx(prefix[0]);

    TrieNode* pfxNode = this->root[index];
    for(int i=1; i < prefix.size(); i++)
    {
        int idx = getIdx(prefix[i]);
        if (pfxNode->_children[idx] == nullptr) {
            return 0;
        }
        pfxNode = pfxNode->_children[idx];
    }
    string suggest;
    int result = 0;
    TrieNode *node;

    if(pfxNode->_terminal){
        resultList[result++] = prefix;
    }

    for (int i = 0; i < 26; i++) {
        node = pfxNode->_children[i];
        int j = 0;

        if(node != nullptr){
            suggest = prefix;
        }

        while(node != nullptr){
            if(node->_children[j] != nullptr){
                suggest += node->_ltr;
                if(node->_terminal){
                    resultList[result++] = suggest;
                    node->_suggested = true;
                }
                node = node->_children[j];
                j = 0;
            } else if (j == 25){
                if(node->_terminal) {
                    if(node->_suggested){
                        node->_suggested = false;
                        if(node != pfxNode->_children[i]) {
                            j = (getIdx(node->_ltr)) + 1;
                            node = node->_parent;
                            suggest = prefix;
                        } else {
                            break;
                        }
                    } else {
                        suggest += node->_ltr;
                        resultList[result++] = suggest;
                        node->_suggested = true;
                    }
                } else if(node != pfxNode->_children[i]) {
                    j = (getIdx(node->_ltr)) + 1;
                    node = node->_parent;
                    suggest = prefix;
                } else {
                    break;
                }
            } else {
                j++;
            }
        }

    }
    return result;
}

void Trie::remove(TrieNode *tn)
{
    if (tn){
        bool hasChildren = false;
        for (int i = 0; i < 26; ++i){
            if (tn->_children[i]){
                hasChildren = true;
            }
        }
        if (!hasChildren){
            delete tn;
            return;
        }
        for (int i = 0; i < 26; i++){
            remove(tn->_children[i]);
        }
    }
}

Trie::~Trie()
{
    for (int i = 0; i < 26; ++i){
        remove(root[i]);
    }
}

Trie::TrieNode *Trie::addTrieNode(const char ltr, TrieNode* parent) {
    TrieNode* tn = new TrieNode(parent);
    for (auto& i : tn->_children) {
        i = nullptr;
    }
    tn->_terminal = false;
    tn->_ltr = ltr;
    tn->_suggested = false;
    return tn;
}
