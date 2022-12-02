//
// Created by Armen on 2022-12-02.
//

#include <iostream>
#include "a3.h"
#include <string>

using namespace std;
int main(int argc, char* argv[]){

    Trie trie;

    for(int i = 0; i < 26; i++){
        cout << trie.returnLetter(i);
    }
    cout << endl;
}