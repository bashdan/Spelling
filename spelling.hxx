#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

#include "trie.hxx"

#ifndef _SPELLING_HXX_
#define _SPELLING_HXX_

#define SBOARD_DIM 15

// SQ_1L = 1* multiplier for character
// SQ_2L = 2* multiplier for character
// SQ_3L = 3* multiplier for character
// SQ_2W = 2* multiplier for placed word
// SQ_3W = 3* multiplier for placed word
typedef enum {
    SQ_1L, SQ_2L, SQ_3L, SQ_2W, SQ_3W
} square_t;

// The board is a matrix of tuplet_t:
//      Square type
//      The character inserted at the position
//      The value of the character at the position (varies)
typedef std::tuple<square_t, const char, const std::size_t> tuple_t;

class SBoard {
    tuple_t **board;
    SBoard(void) {
        board = new tuple_t*[SBOARD_DIM];
        for (auto i = 0; i < SBOARD_DIM; i++)
            board[i] = new tuple_t[SBOARD_DIM];
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
// This function generates all permutations of s, checks them against words in t,
// and returns the remainder in vecOut.
std::vector<std::string> &anagram(std::vector<std::string> &vecOut, Trie &t, const std::string &str);
// This function generates all permutations of s with wildcards *, %, or ?, checks the potential word
// existence in t, and returns the remainder in vecOut.
std::vector<std::string> &anagram_wildcards(std::vector<std::string> &vecOut, Trie &t, const std::string &str);
// This function generates all permutations of words of the powerset of s (including wildcards)
std::vector<std::string> &anagram_exhaustively(std::vector<std::string> &vecOut, Trie &t, const std::string &str);

#endif
