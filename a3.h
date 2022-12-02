#include <string>
using namespace std;

class Trie{
	
	
	struct TriNode{

		char* letter = '';
		TriNode* next;
		TriNode* prev;
	}

	TriNode alphabet[25] = {};

public:
	Trie(const std::string wordList[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int beginsWith(const std::string& prefix, std::string resultList[]) const;
	~Trie();	
};
