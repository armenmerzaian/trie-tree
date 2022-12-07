#include "a3.h"
#include <string>


int getIdx(char ch){
  return ch -'a';
}

Trie::Trie(){
    string alphabet[] = {"a", "b", "c", "d", "e",
                        "f", "g", "h", "i", "j",
                        "k", "l", "m", "n", "o",
                        "p", "q", "r", "s", "t",
                        "u", "v", "w", "x", "y",
                        "z"};
    int j = 0;
    for(auto& i : root){
        i = addTrieNode(alphabet[j++]);
    }
}

Trie::Trie(const std::string wordList[],int sz){
    for(int i = 0; i < sz; i++){
        string currWord = wordList[i];
        int index = getIdx(currWord[0]);
        TrieNode* temp = this->root[index];
        temp->_ltr = currWord[0];
        for (int j=1; j < currWord.length(); j++) {
            int idx = getIdx(currWord[j]);
            if (temp->_children[idx] == nullptr) {
                temp->_children[idx] = addTrieNode(to_string(currWord[j]));
            }
            // Go down a level, to the child referenced by idx
            // since we have a prefix match
            if(j != currWord.length() - 1){
                temp = temp->_children[idx];
            }
        }
        // At the end of the word, mark this node as the leaf node
        temp->_terminal = true;
        //return root;
    }
}



void Trie::addWord(const std::string& newWord){
    int index = getIdx(newWord[0]);
    TrieNode* temp = this->root[index];
    if(temp->_ltr == ""){
        temp = addTrieNode(to_string(newWord[0]));
    }
    for (int i=1; i < newWord.length(); i++) {
        int idx = getIdx(newWord[i]);
        if (temp->_children[idx] == nullptr) {
            temp->_children[idx] = addTrieNode(to_string(newWord[i]));
        }
        if(i != newWord.length() - 1){
            temp = temp->_children[idx];
        }
    }
    temp->_terminal = true;
}

bool Trie::lookup(const std::string& word) const{
    // Searches for word in the Trie
    int index = getIdx(word[0]);
    TrieNode* temp = this->root[index];
    if(temp->_ltr.empty()){
        return false;
    }
    for(int i=1; i < word.size(); i++)
    {
        int idx = getIdx(word[i]);
        if (temp->_children[idx] == nullptr) {
            return false;
        }
        if(i != word.size() - 1){
            temp = temp->_children[idx];
        }
    }
    if (temp->_terminal){
        return true;
    }
    return false;
}

int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const{
    int index = getIdx(prefix[0]);

    TrieNode* temp = this->root[index];
    if(temp->_ltr.empty() ){
        return 0;
    }
    for(int i=1; i < prefix.size(); i++)
    {
        int idx = getIdx(prefix[i]);
        if (temp->_children[idx] == nullptr) {
            return 0;
        }
        if(i != prefix.size() - 1){
            temp = temp->_children[idx];
        }
    }
    if(temp->_terminal){
        TrieNode* prefixTrie;
        for(auto& a : temp->_children){
            for(int j = 0; j < 26; j++){
                if(a->_children[j] != nullptr){

                }
            }
        }
    }
}

Trie::~Trie(){

}

Trie::TrieNode *Trie::addTrieNode(const string ltr) {
    TrieNode* tn = new TrieNode();
    for (auto& i : tn->_children) {
        i = nullptr;
    }
    tn->_terminal = false;
    tn->_ltr = ltr;
    return tn;
}
