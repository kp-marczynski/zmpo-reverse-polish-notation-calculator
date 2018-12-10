//
// Created by krispy1396 on 14.11.2017.
//

#ifndef ZMPO_LISTA3_LOGGER_H
#define ZMPO_LISTA3_LOGGER_H

#include <sstream>

using namespace std;

#define SUCCESS_CODE 200
#define ARGUMENT_NOT_FOUND 1
#define VARIABLE_NOT_INITIATED 2
#define DIVISION_BY_ZERO 3
#define NOT_ALLOWED_CHARS_IN_ARGUMENT 4
#define NO_LETTERS_IN_VARIABLE 5
#define NODE_OF_WRONG_TYPE 6
#define ARGUMENT_IS_NOT_NUMBER 7
#define ARGUMENTS_LEFT 8

class ErrorLogger {
private:
    int errorCode;

public:
    ErrorLogger(int errorCode);

    string toString();
};


#endif //ZMPO_LISTA3_LOGGER_H
