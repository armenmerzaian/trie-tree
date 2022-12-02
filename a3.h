#include <string>
#include <cstring>

#define ALPHABET 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'

using namespace std;

class Trie{

    struct TrieNode{
        string _ltr; // Storing for printing purposes only
        TrieNode* _children[26];
        bool _terminal;

        TrieNode(){};
        TrieNode operator = (TrieNode *rhs) {
            TrieNode tn;
            tn._ltr = rhs->_ltr;
            for (int i = 0; i < 26; i++){
                tn._children[i] = rhs->_children[i];
            }
            tn._terminal = rhs->_terminal;
            return tn;
        }

	};

    TrieNode* root[26];

public:
    Trie();
	Trie(const std::string wordList[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int beginsWith(const std::string& prefix, std::string resultList[]) const;

    string returnLetter(int i){
        return root[i]->_ltr;
    }

    TrieNode* addTrieNode(const string ltr);

	~Trie();	
};
