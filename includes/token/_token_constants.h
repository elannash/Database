#ifndef TOKEN_CONSTANTS_H
#define TOKEN_CONSTANTS_H

// regular Token types
const int TOKEN_UNKNOWN = -1;
const int TOKEN_STR = 1;
const int OPERATOR = 2;
const int RELATIONAL = 3;
const int LOGICAL = 4;
const int LEFT_PAREN = 5;
const int RIGHT_PAREN = 6;
const int RESULT_SET = 7;

// TokenStr string types
const int TOKEN_ALPHA = 11;
const int TOKEN_NUMBER = 12;
const int TOKEN_SPACE = 13;
const int TOKEN_OPERATOR = 14;
const int TOKEN_PUNC = 15;
const int TOKEN_MISC = 16;

// Token precedences
const int UNKNOWN_PREC = -1;
const int RELATIONAL_PREC = 3;
const int LOGICAL_NOT_PREC = 2;
const int LOGICAL_AND_PREC = 1;
const int LOGICAL_OR_PREC = 0;

#endif /* TOKEN_CONSTANTS_H */
