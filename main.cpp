#include <iostream>
#include <vector>
#include <algorithm>

#define COLLINS "./dictionaries/Collins Scrabble Words (2019).txt"
#define TWL3    "./dictionaries/TWL3.txt"

#include "trie.hxx"
#include "spelling.hxx"

int main() {
    std::vector<std::string> v;
    
    Trie t(COLLINS);

    SBoard b(SCRABBLE);
    b.prettyprint();
    
    return 0;
}
