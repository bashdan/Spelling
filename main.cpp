#include <iostream>
#include <vector>
#include <algorithm>

#include "trie.hxx"
#include "spelling.hxx"

int main() {
    std::vector<std::string> v;
    
    Trie t(COLLINS);

    v = anagram_exhaustively(v, t, "DANIEL");
    for (auto e : v) {
        std::cout << e << "\n";
    }

    benchmark("DANIEL");
    SBoard board(SCRABBLE);
    board.prettyprint();

    
    return 0;
}
