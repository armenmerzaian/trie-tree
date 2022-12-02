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
        for (int j=1; currWord[j] < currWord.length(); j++) {
            int idx = getIdx(currWord[j]);
            if (temp->_children[idx] == nullptr) {
                temp->_children[idx] = addTrieNode(to_string(currWord[j]));
            }
            // Go down a level, to the child referenced by idx
            // since we have a prefix match
            temp = temp->_children[idx];
        }
        // At the end of the word, mark this node as the leaf node
        temp->_terminal = true;
        //return root;
    }
}



void Trie::addWord(const std::string& newWord){

}

bool Trie::lookup(const std::string& word) const{
    // Searches for word in the Trie
    /*int indexi
    TrieNode* temp = this->root[word[0]];

    for(int i=0; i < word.size(); i++)
    {
        int index = getIdx(word[i]);
        if (temp->children[position] == NULL)
            return true;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return true;
    return false;*/
}

int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const{

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
