//
// Created by krispy1396 on 14.11.2017.
//

#include "ErrorLogger.h"

const char *SUCCESS_MESSAGE = "Wszystko OK\n";

const char *ARGUMENT_NOT_FOUND_MESSAGE = "Podano za malo argumentow. Nieuzupelnione wezly zostana uzupelnione wartosciami 1\n";

const char *VARIABLE_NOT_INITIATED_MESSAGE = "Nie mozna obliczyc wyrazenia, bo przynajmniej do jednej zmiennej nie przypisano wartosci\n";

const char *DIVISION_BY_ZERO_MESSAGE = "Nie mozna ukonczyc obliczen, bo wystapilo dzieleni przez 0\n";

const char *NOT_ALLOWED_CHARS_IN_ARGUMENT_MESSAGE = "W nazwie argumentu znalazl sie niedozwolony znak, ktory zostal automatycznie usuniety\n";

const char *NO_LETTERS_IN_VARIABLE_MESSAGE = "Po usunieciu niedozwolonych znakow z nazwy zmiennej nie znaleziono ani jednej litery (wymagane minimum istnienia zmiennej)\n";

const char *NODE_OF_WRONG_TYPE_MESSAGE = "Nie rozpoznano typu przetwarzanego wezla.\n";

const char *ARGUMENT_IS_NOT_NUMBER_MESSAGE = "Argument musi byc liczba a nie jest.\n";

const char *ARGUMENTS_LEFT_MESSAGE = "Podano za duzo parametrow. Nadmiorowe parametry pominieto.\n";

ErrorLogger::ErrorLogger(int errorCode) {
    this->errorCode = errorCode;
}

string ErrorLogger::toString() {
    switch (errorCode) {
        case SUCCESS_CODE:
            return SUCCESS_MESSAGE;
        case ARGUMENT_NOT_FOUND:
            return ARGUMENT_NOT_FOUND_MESSAGE;
        case VARIABLE_NOT_INITIATED:
            return VARIABLE_NOT_INITIATED_MESSAGE;
        case DIVISION_BY_ZERO:
            return DIVISION_BY_ZERO_MESSAGE;
        case NOT_ALLOWED_CHARS_IN_ARGUMENT:
            return NOT_ALLOWED_CHARS_IN_ARGUMENT_MESSAGE;
        case NO_LETTERS_IN_VARIABLE:
            return NO_LETTERS_IN_VARIABLE_MESSAGE;
        case NODE_OF_WRONG_TYPE:
            return NODE_OF_WRONG_TYPE_MESSAGE;
        case ARGUMENT_IS_NOT_NUMBER:
            return ARGUMENT_IS_NOT_NUMBER_MESSAGE;
        case ARGUMENTS_LEFT:
            return ARGUMENTS_LEFT_MESSAGE;
        default:
            return "";
    }
}
