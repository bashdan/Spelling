#include <iostream>
#include "trie.hxx"

int main() {
    Trie t("dict.txt");
    t.print();

    t.insert("YPSILON");
    t.insert("ZOOLOGY");
    t.print();
    return 0;
}