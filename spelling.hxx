#ifndef _SPELLING_HXX_
#define _SPELLING_HXX_

#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

#include "trie.hxx"
#include "rules.hxx"

// The board is a matrix of tuplet_t:
//      Square type
//      The character inserted at the position
//      The value of the character at the position (varies)
typedef std::tuple<square_t, char, std::size_t> tuple_t;

class SBoard {

public:
    tuple_t **board;
    SBoard(void) {
        board = new tuple_t*[SBOARD_DIM];
        for (auto i = 0; i < SBOARD_DIM; i++) {
            board[i] = new tuple_t[SBOARD_DIM];
        }
    }
    SBoard(enum board_layout bl) {
        switch (bl) {
            case SCRABBLE:
                this->board = new tuple_t*[SCRABBLE_DIM];
                for (auto i = 0; i < SCRABBLE_DIM; i++) {
                    this->board[i] = new tuple_t[SCRABBLE_DIM];
                    for (auto j = 0; j < SCRABBLE_DIM; j++) {
                        this->board[i][j] = 
                            std::make_tuple(SCRABBLE_LAYOUT[i][j], ' ', 0);
                    }
                }
            break;
            case WORDS_WITH_FRIENDS:
                this->board = new tuple_t*[WORDS_WITH_FRIENDS_DIM];
                for (auto i = 0; i < WORDS_WITH_FRIENDS_DIM; i++) {
                    this->board[i] = new tuple_t[WORDS_WITH_FRIENDS_DIM];
                    for (auto j = 0; j < WORDS_WITH_FRIENDS_DIM; j++) {
                        this->board[i][j] = 
                            std::make_tuple(WORDS_WITH_FRIENDS_LAYOUT[i][j], ' ', 0);
                    }
                }
            break;
        }
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
                if (y == 7 && x == 7) { // center special case
                    std::cout << "\u00A4";
                }
                else {
                    switch (std::get<0>(this->board[y][x])) {
                        case SQ_1L: std::cout << ' '; break;
                        case SQ_2L: std::cout << "\u00B2"; break;
                        case SQ_3L: std::cout << "\u00B3"; break;
                        case SQ_2W: std::cout << '2'; break;
                        case SQ_3W: std::cout << '3'; break;
                    }
                }
                std::cout << std::get<1>(this->board[y][x]) << " ";
            }
            std::cout << "|\n" << BORDER << "\n";
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
