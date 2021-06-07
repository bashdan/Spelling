#include <vector>
#include <string>
#include <algorithm>

#include "trie.hxx"

#ifndef _SPELLING_HXX_
#define _SPELLING_HXX_

#define SBOARD_DIM 15

typedef enum {
    SQ_1L, SQ_2L, SQ_3L, SQ_2W, SQ_3W
} Square_t;

class SBoard {
    Square_t **board;
    SBoard(void) {
        board = new Square_t*[SBOARD_DIM];
        for (auto i = 0; i < SBOARD_DIM; i++)
            board[i] = new Square_t[SBOARD_DIM];
    }
    ~SBoard(void) {
        for (auto i = 0; i < SBOARD_DIM; i++)
            delete board[i];
        delete board;
    }
    void prettyprint(void) {
        static const std::string BORDER = 
            "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+";
        std::cout << BORDER << "\n";
        for (auto y = 0; y < SBOARD_DIM; y++) {
            for (auto x = 0; x < SBOARD_DIM; x++) {
                std::cout << "|";
                /* TODO
                switch (this->board[y][x]) {
                    case SQ_1L: std::wcout << 0xB9
                }
                */
            }
            std::cout << BORDER << "\n";
        }
    }
};

void transform_file(const std::string &filename_in, const std::string &filename_out);
// A function to generate all permutations of a string with alphabetical characters
std::vector<std::string> &permute(std::vector<std::string> &vecOut, const std::string &str);
// This function generates all permutations checked against words marked as such in the Trie
std::vector<std::string> &anagram(std::vector<std::string> &vecOut, Trie &t, const std::string &str);
// This function generates all permutations of words utilizing wildcards against the words in the Trie
std::vector<std::string> &anagram_wildcards(std::vector<std::string> &vecOut, Trie &t, const std::string &str);

#endif
