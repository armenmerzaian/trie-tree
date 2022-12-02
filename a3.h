#include <string>
using namespace std;

class Trie{

public:
	Trie(const std::string wordList[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int beginsWith(const std::string& prefix, std::string resultList[]) const;
	~Trie();	
};
