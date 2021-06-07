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

enum orientation {
    HORIZONTAL, VERTICAL
};

class SBoard {

public:
    tuple_t **board;
    enum board_layout layout;
    SBoard(void) {
        board = new tuple_t*[SBOARD_DIM];
        for (auto i = 0; i < SBOARD_DIM; i++) {
            board[i] = new tuple_t[SBOARD_DIM];
        }
    }
    SBoard(enum board_layout bl) {
        this->layout = bl;
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
    bool isSafeToPlace(const std::string &s, const std::size_t x, const std::size_t y, enum orientation o, Trie &t) {

        std::size_t len = s.length();
        // Bounds checking
        switch (this->layout) {
            case SCRABBLE_LAYOUT: // TODO: fix logic
                // A flag to ensure we're placing adjacent to existing word(s).
                bool contiguousPlacement = false;
                if (o == HORIZONTAL) {
                    // Ensure the word doesn't wrap
                    if ((len+x) >= SCRABBLE_DIM) return false;
                    // Ensure that we don't overwrite existing words on board
                    for (auto i = 0; i < len; i++) 
                        if (std::get<1>(this->board[y][x+i]) != ' ') return false;
                    // Check above
                    if (y > 0) {
                        for (auto i = 0; i < len; i++) {
                            std::string new_word = std::string(s.at(i));
                            bool adjacentWords = false;
                            for (auto j = 1; ((y-j) >= 0) && (std::get<1>(this->board[y-j][x+i]) != ' '); j++) {
                                adjacentWords = true;
                                contiguousPlacement = true;
                                new_word += std::get<1>(this->board[y-j][x+i]);
                            }
                            if (adjacentWords && !t.isWord(new_word)) return false;
                        }
                    }
                    // Check below
                    if (y < (SCRABBLE_DIM-1)) {
                        for (auto i = 0; i < len; i++) {
                            std::string new_word = std::string(s.at(i));
                            bool adjacentWords = false;
                            for (auto j = 1; ((y+j) < SCRABBLE_DIM) && (std::get<1>(this->board[y+j][x+i]) != ' '); j++) {
                                adjacentWords = true;
                                contiguousPlacement = true;
                                new_word += std::get<1>(this->board[y+j][x+i]);
                            }
                            if (adjacentWords && !t.isWord(new_word)) return false;
                        }
                    }
                    // Check left: existing characters prepend s
                    if ((x > 0) && (std::get<1>(this->board[y][x-1]) != ' ')) {
                        contiguousPlacement = true;
                        std::string new_word = "";
                        int occ = x;
                        occ--;
                        while (occ >= 0 && std::get<1>(this->board[y][occ]) != ' ') {
                            occ--;
                        }
                        // occ is -1 (and board is filled to left edge) || occ is on an empty square
                        for (occ += 1; occ < x; occ++) {
                            new_word += std::get<1>(this->board[y][occ]);
                        }
                        new_word += s;
                        if (!t.isWord(new_word)) return false;
                    }
                    // Check right: existing characters append to s
                    if (x < (SCRABBLE_DIM-1)) {
                        std::string new_word(s);
                        for (auto i = x+len; (i < SCRABBLE_DIM) && (std::get<1>(this->board[y][i]) != ' '); i++) {
                            contiguousPlacement = true;
                            new_word += std::get<1>(this->board[y][i]);
                        }
                        if (!t.isWord(new_word)) return false;
                    }
                }
                else {
                    // Ensure the word doesn't wrap
                    if ((len+y) >= SCRABBLE_DIM) return false;
                    // Ensure that we don't overwrite existing words on board
                    for (auto i = 0; i < len; i++) 
                        if (std::get<1>(this->board[y+i][x]) != ' ') return false;
                    // Check above
                    if (y > 0) {
                        for (auto i = 0; i < len; i++) {
                            std::string new_word = std::string(s.at(i));
                            bool adjacentWords = false;
                            for (auto j = 1; ((y-j) >= 0) && (std::get<1>(this->board[y-j][x+i]) != ' '); j++) {
                                adjacentWords = true;
                                contiguousPlacement = true;
                                new_word += std::get<1>(this->board[y-j][x+i]);
                            }
                            if (adjacentWords && !t.isWord(new_word)) return false;
                        }
                    }
                    // Check below
                    if (y < (SCRABBLE_DIM-1)) {
                        for (auto i = 0; i < len; i++) {
                            std::string new_word = std::string(s.at(i));
                            bool adjacentWords = false;
                            for (auto j = 1; ((y+j) < SCRABBLE_DIM) && (std::get<1>(this->board[y+j][x+i]) != ' '); j++) {
                                adjacentWords = true;
                                contiguousPlacement = true;
                                new_word += std::get<1>(this->board[y+j][x+i]);
                            }
                            if (adjacentWords && !t.isWord(new_word)) return false;
                        }
                    }
                    // Check above: existing characters prepend s
                    if ((y > 0) && (std::get<1>(this->board[y-1][x]) != ' ')) {
                        contiguousPlacement = true;
                        std::string new_word = "";
                        int occ = y;
                        occ--;
                        while (occ >= 0 && std::get<1>(this->board[occ][x]) != ' ') {
                            occ--;
                        }
                        // occ is -1 (and board is filled to top edge) || occ is on an empty square
                        for (occ += 1; occ < y; occ++) {
                            new_word += std::get<1>(this->board[occ][x]);
                        }
                        new_word += s;
                        if (!t.isWord(new_word)) return false;
                    }
                    // Check right: existing characters append to s
                    if (x < (SCRABBLE_DIM-1)) {
                        std::string new_word(s);
                        for (auto i = x+len; (i < SCRABBLE_DIM) && (std::get<1>(this->board[y][i]) != ' '); i++) {
                            contiguousPlacement = true;
                            new_word += std::get<1>(this->board[y][i]);
                        }
                        if (!t.isWord(new_word)) return false;
                    }
                }
            break;
            case WORDS_WITH_FRIENDS_LAYOUT:
                if (o == HORIZONTAL)
                    if ((len+x) >= WORDS_WITH_FRIENDS_DIM) return false;
                else 
                    if ((len+y) >= WORDS_WITH_FRIENDS_DIM) return false;
        }
        // Existing word overwrite checking
        if (o == HORIZONTAL) {
            
            // Existing words may touch above
            if (y > 0) {
                for (auto i = 0; i < len; i++) {
                    std::string new_word = "";
                    for (auto j = 1; (y-j) >= 0 && std::get<1>(this->board[y-j][x+i]) != ' '; j++) {
                        new_word += std::get<1>(this->board[y-j][x+i]);
                    }
                    if (!t.isWord(new_word)) return false;
                }
            } else if (this->layout == SCRABBLE && y < (SCRABBLE_DIM-1)) {
                for (auto i = 0; i < len; i++) {
                    std::string new_word = "";
                    for (auto j = 1; (y+j) < SCRABBLE_DIM && std::get<1>(this->board[y+j][x+i]) != ' '; j++) {
                        new_word += std::get<1>(this->board[y+j][x+i]);
                    }
                    if (!t.isWord(new_word)) return false;
                }
            } else if (this->layout == WORDS_WITH_FRIENDS && y < (WORDS_WITH_FRIENDS_DIM-1)) {
                for (auto i = 0; i < len; i++) {
                    std::string new_word = "";
                    for (auto j = 1; (y+j) < WORDS_WITH_FRIENDS_DIM && std::get<1>(this->board[y+j][x+i]) != ' '; j++) {
                        new_word += std::get<1>(this->board[y+j][x+i]);
                    }
                    if (!t.isWord(new_word)) return false;
                }
            }
        } else {
            for (auto i = 0; i < len; i++)
                if (std::get<1>(this->board[y+i][x]) != ' ') return false;
        }

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
                        case SQ_2L: std::cout << "\u00B2"; break; // superscript 2
                        case SQ_3L: std::cout << "\u00B3"; break; // superscript 3
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
