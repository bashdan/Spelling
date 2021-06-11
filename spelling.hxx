#ifndef _SPELLING_HXX_
#define _SPELLING_HXX_

#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <chrono> // benchmark timing

#include "trie.hxx"
#include "rules.hxx"

#define COLLINS "./dictionaries/Collins Scrabble Words (2019).txt"
#define TWL3    "./dictionaries/TWL3.txt"

void benchmark(const std::string &str);

// The board is a matrix of tuplet_t:
//      Square type
//      The character inserted at the position
//      The value of the character at the position (varies)
typedef std::tuple<square_t, char, std::size_t> tuple_t;

enum orientation {
    HORIZONTAL, VERTICAL
};

using namespace std;

class SBoard {
private:
    std::size_t board_dim_;
    square_t **squares_;
    char **chars_;
    std::size_t **values_;
public:
    SBoard(void) {
        // defaults to 15x15
        this->board_dim_ = SBOARD_DIM;
        squares_ = new square_t*[this->board_dim_];
        chars_   = new char*[this->board_dim_];
        values_  = new size_t*[this->board_dim_];
        
        for (auto i = 0; i < this->board_dim_; i++) {
            squares_[i] = new square_t[this->board_dim_]();
            chars_[i]   = new char[this->board_dim_]();
            values_[i]  = new size_t[this->board_dim_]();
        }
    }
    SBoard(enum board_layout bl) {
        size_t board_size = 1;
        switch (bl) {
            case SCRABBLE: board_size = SCRABBLE_DIM; break;
            case WORDS_WITH_FRIENDS: board_size = WORDS_WITH_FRIENDS_DIM; break;
        }

        this->board_dim_ = board_size;
        squares_ = new square_t*[board_dim_];
        chars_   = new char*[board_dim_];
        values_  = new size_t*[board_dim_];
        
        for (auto i = 0; i < this->board_dim_; i++) {
            squares_[i] = new square_t[board_dim_];
            chars_[i]   = new char[board_dim_];
            values_[i]  = new size_t[board_dim_];
        }

        switch (bl) {
            case SCRABBLE: {
                for (auto y = 0; y < board_size; y++) {
                    for (auto x = 0; x < board_size; x++) {
                        squares_[y][x] = SCRABBLE_LAYOUT[y][x];
                        chars_[y][x] = ' ';
                        values_[y][x] = 0;
                    }
                }
                break;
            }
            case WORDS_WITH_FRIENDS: {
                for (auto y = 0; y < board_size; y++) {
                    for (auto x = 0; x < board_size; x++) {
                        squares_[y][x] = WORDS_WITH_FRIENDS_LAYOUT[y][x];
                        chars_[y][x] = ' ';
                        values_[y][x] = 0;
                    }
                }
                break;
            }
        }
    }
    ~SBoard(void) {
        for (auto i = 0; i < this->board_dim_; i++) {
            delete this->squares_[i];
            delete this->chars_[i];
            delete this->values_[i];
        }
        delete squares_;
        delete chars_;
        delete values_;
    }

    void prettyprint(void) {
        static const std::string BORDER = 
            "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+";
        const size_t dim = this->board_dim_;
        std::cout << BORDER << "\n";
        for (auto y = 0; y < dim; y++) {
            for (auto x = 0; x < dim; x++) {
                std::cout << "|";
                if (y == 7 && x == 7) { // center special case
                    std::cout << "\u00A4";
                }
                else {
                    switch (this->squares_[y][x]) {
                        case SQ_1L: std::cout << ' '; break;
                        case SQ_2L: std::cout << "\u00B2"; break; // superscript 2
                        case SQ_3L: std::cout << "\u00B3"; break; // superscript 3
                        case SQ_2W: std::cout << '2'; break;
                        case SQ_3W: std::cout << '3'; break;
                    }
                }
                std::cout << this->chars_[y][x] << " ";
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
