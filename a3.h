#include <string>
#include <cstring>
#include <iostream>


using namespace std;

class Trie{

    struct TrieNode{
        char _ltr;
        TrieNode* _children[26];
        TrieNode* _parent;
        bool _terminal;
        bool _suggested;

        TrieNode(TrieNode* parent){
            _parent = parent;
        };
        TrieNode& operator = (const TrieNode& rhs) {
            _ltr = rhs._ltr;
            for (int i = 0; i < 26; i++){
                _children[i] = rhs._children[i];
            }
            _terminal = rhs._terminal;
            return *this;
        }

	};

    TrieNode* root[26];

public:
    Trie();
	Trie(const std::string wordList[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int beginsWith(const std::string& prefix, std::string resultList[]) const;

    void searchHelper(const std::string& prefix, std::string resultList[], int& counter, TrieNode* tempNode) const;
    static TrieNode* addTrieNode(char ltr, TrieNode* parent);
    void remove(TrieNode *node);
	~Trie();	
};
