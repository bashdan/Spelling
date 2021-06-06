#include <vector>
#include <string>
#include <algorithm>

#include "trie.hxx"

#ifndef _SPELLING_HXX_
#define _SPELLING_HXX_

// A function to generate all permutations of a string with alphabetical characters
std::vector<std::string> &permute(std::vector<std::string> &vecOut, const std::string &str);
// This function generates all permutations checked against words marked as such in the Trie
std::vector<std::string> &anagram(std::vector<std::string> &vecOut, Trie &t, const std::string &str);
// This function generates all permutations of words utilizing wildcards against the words in the Trie
std::vector<std::string> &anagram_wildcards(std::vector<std::string> &vecOut, Trie &t, const std::string &str);

#endif
