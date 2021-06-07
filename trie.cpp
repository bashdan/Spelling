#include <iostream>
#include <vector>
#include <algorithm>

#include "trie.hxx"
#include "spelling.hxx"

int main() {
    std::vector<std::string> v;
    
    Trie t("Collins Scrabble Words (2019).txt");

    v = anagram_exhaustively(v, t, "EA**");
    for (auto w : v) {
        std::cout << w << "\n";
    }
    std::cout << v.size() << " words computed\n";
    return 0;
}
