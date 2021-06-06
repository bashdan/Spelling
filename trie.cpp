#include <iostream>
#include <vector>
#include <algorithm>

#include "trie.hxx"
#include "spelling.hxx"

int main() {
    std::vector<std::string> v;

    Trie t("dict.txt");
    v = anagram_wildcards(v, t, "AB**");
    for (auto w : v) {
        std::cout << w << "\n";
    }
    return 0;
}
