#ifndef _RULES_HXX_
#define _RULES_HXX_

#include <map>
#include <vector>

#include "spelling.hxx"

// SQ_1L = 1* multiplier for character
// SQ_2L = 2* multiplier for character
// SQ_3L = 3* multiplier for character
// SQ_2W = 2* multiplier for placed word
// SQ_3W = 3* multiplier for placed word
typedef enum square_type {
    SQ_1L, SQ_2L, SQ_3L, SQ_2W, SQ_3W
} square_t;

#define SBOARD_DIM 15
#define SCRABBLE_DIM 15
#define WORDS_WITH_FRIENDS_DIM 15

enum board_layout {
    SCRABBLE, WORDS_WITH_FRIENDS
};

static const std::map<char, unsigned> SCRABBLE_CHAR_POINT_MAP = {
    { 'A', 1 }, { 'B', 3 }, { 'C', 3 }, { 'D', 2 }, { 'E', 1 },
    { 'F', 4 }, { 'G', 2 }, { 'H', 4 }, { 'I', 1 }, { 'J', 8 },
    { 'K', 5 }, { 'L', 1 }, { 'M', 3 }, { 'N', 1 }, { 'O', 1 },
    { 'P', 3 }, { 'Q',10 }, { 'R', 1 }, { 'S', 1 }, { 'T', 1 },
    { 'U', 1 }, { 'V', 4 }, { 'W', 4 }, { 'X', 8 }, { 'Y', 4 },
    { 'Z', 10}, { '*', 0 }, { '?', 0 }, { '%', 0 }
};

static const std::vector<unsigned> SCRABBLE_CHAR_COUNT = {
    9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4,
    6, 4, 2, 2, 1, 2, 1, 2 // 2 blanks
};

static const square_t SCRABBLE_LAYOUT[SCRABBLE_DIM][SCRABBLE_DIM] = {
    { SQ_3W, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_3W },
    { SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L },
    { SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L },
    { SQ_2L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_2L },
    { SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L },
    { SQ_3W, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_3W },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L },
    { SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_1L },
    { SQ_2L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_2L },
    { SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L },
    { SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L },
    { SQ_3W, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_3W }
};

static const std::map<char, unsigned> WORDS_WITH_FRIENDS_CHAR_POINT_MAP = {
    { 'A', 1 }, { 'B', 4 }, { 'C', 4 }, { 'D', 2 }, { 'E', 1 },
    { 'F', 4 }, { 'G', 3 }, { 'H', 3 }, { 'I', 1 }, { 'J',10 },
    { 'K', 5 }, { 'L', 2 }, { 'M', 4 }, { 'N', 2 }, { 'O', 1 },
    { 'P', 4 }, { 'Q',10 }, { 'R', 1 }, { 'S', 1 }, { 'T', 1 },
    { 'U', 2 }, { 'V', 5 }, { 'W', 4 }, { 'X', 8 }, { 'Y', 3 },
    { 'Z', 10}, { '*', 0 }, { '?', 0 }, { '%', 0 }
};

static const std::vector<unsigned> WORDS_WITH_FRIENDS_CHAR_COUNT = {
    9, 2, 2, 5, 13, 2, 3, 4, 8, 1, 1, 4, 2, 5, 8, 2, 1, 6, 5, 
    7, 4, 2, 2, 1, 2, 1, 2 // 2 blanks
};

static const square_t WORDS_WITH_FRIENDS_LAYOUT[WORDS_WITH_FRIENDS_DIM][WORDS_WITH_FRIENDS_DIM] = {
    { SQ_1L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2L, SQ_1L },
    { SQ_3W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_3W },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L },
    { SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_3L },
    { SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L },
    { SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_3L },
    { SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L },
    { SQ_3W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_3W },
    { SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2L, SQ_1L },
    { SQ_1L, SQ_1L, SQ_2L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_1L, SQ_2W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_1L },
    { SQ_1L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_3L, SQ_1L, SQ_3L, SQ_1L, SQ_1L, SQ_3W, SQ_1L, SQ_1L, SQ_1L }
};

#endif