#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char OPERATORS[] = "><=!+-*/%&|";
const char PUNC[] = "()?.,:;'`~\""; // does not contain '!'

const int START_ALPHA = 1;
const int START_NUMBER = 2;
const int START_SPACE = 5;
const int START_OPERATOR = 6;
const int START_PUNC = 12;
const int START_MISC = 13;

const int END_ALPHA = 1;
const int END_NUMBER = 4;
const int END_SPACE = 5;
const int END_OPERATOR = 11;
const int END_PUNC = 12;

const int SUCCESS_STATE = 1;
const int FAIL_STATE = -1;
const int FAIL_STATE_POS = -1;

#endif /* CONSTANTS_H */