//
// Created by krispy1396 on 12.11.2017.
//

#include <iostream>
#include "Node.h"

const char *PLUS_SIGN = "+";
const char *MINUS_SIGN = "-";
const char *MULTIPLICATION_SIGN = "*";
const char *DIVISION_SIGN = "/";
const char *SINE_SIGN = "sin";
const char *COSINE_SIGN = "cos";
const char SPACE = ' ';

const char *NUMBER_TEMPLATE = "^-?\\d+";


int Node::initializeNode(const string &inputLine, unsigned long &currentPosition, vector<Node *> &variables) {
    string argument = getArgumentFromInputLine(inputLine, currentPosition);
    int resultCode = SUCCESS_CODE;
    regex regexIsNumber(NUMBER_TEMPLATE);
    bool isNumber = regex_match(argument, regexIsNumber);
    if (argument.empty()) {
        resultCode = ARGUMENT_NOT_FOUND;
        logs->push_back(new ErrorLogger(resultCode));
        this->nodeType = VALUE;
        this->value = 1;
        this->numberOfChildren = 0;
    } else if (isNumber) {
        this->nodeType = VALUE;
        this->value = stoi(argument);
        this->numberOfChildren = 0;
    } else if (argument == PLUS_SIGN) {
        this->nodeType = ADDITION_OPERATION;
        this->numberOfChildren = 2;
    } else if (argument == MINUS_SIGN) {
        this->nodeType = SUBSTRACTION_OPERATION;
        this->numberOfChildren = 2;
    } else if (argument == MULTIPLICATION_SIGN) {
        this->nodeType = MULTIPLICATION_OPERATION;
        this->numberOfChildren = 2;
    } else if (argument == DIVISION_SIGN) {
        this->nodeType = DIVISION_OPERATION;
        this->numberOfChildren = 2;
    } else if (argument == SINE_SIGN) {
        this->nodeType = SINE_OPERATION;
        this->numberOfChildren = 1;
    } else if (argument == COSINE_SIGN) {
        this->nodeType = COSINE_OPERATION;
        this->numberOfChildren = 1;
    } else {
        string checkArgument = argument;
        checkArgument.erase(remove_if(checkArgument.begin(), checkArgument.end(), [](unsigned char x) {
            return !((x >= '0' && x <= '9') || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
        }));
        if (checkArgument.length() != argument.length()) {
            resultCode = NOT_ALLOWED_CHARS_IN_ARGUMENT;
        }
        argument = checkArgument;
        checkArgument.erase(remove_if(checkArgument.begin(), checkArgument.end(), [](unsigned char x) {
            return !((x >= '0' && x <= '9'));
        }));
        if (argument.length() == checkArgument.length()) {
            resultCode = NO_LETTERS_IN_VARIABLE;
        }
        if (resultCode != SUCCESS_CODE) {
            logs->push_back(new ErrorLogger(resultCode));
        }
        this->nodeType = VARIABLE;
        this->variableName = argument;
        this->numberOfChildren = 0;
        variables.push_back(this);
    }
    int childrenResultCode = initializeChildren(inputLine, currentPosition, variables);
    if (childrenResultCode != SUCCESS_CODE) {
        resultCode = childrenResultCode;
    }
    return resultCode;
}

int Node::initializeChildren(const string &inputLine, unsigned long &currentPosition, vector<Node *> &variables) {
    this->childrenList = new Node *[getNumberOfChildren()];
    int resultCode = SUCCESS_CODE;
    for (int i = 0; i < getNumberOfChildren(); ++i) {
        this->childrenList[i] = new Node(logs);
        resultCode = this->childrenList[i]->initializeNode(inputLine, currentPosition, variables);
    }
    return resultCode;
}

int Node::computeValue() {
    int resultCode = SUCCESS_CODE;
    for (int i = 0; i < getNumberOfChildren() && resultCode == SUCCESS_CODE; ++i) {
        resultCode = this->childrenList[i]->computeValue();
    }
    if (resultCode == SUCCESS_CODE) {
        switch (this->nodeType) {
            case VALUE:
                break;
            case VARIABLE:
                if (!this->valueComputed) {
                    resultCode = VARIABLE_NOT_INITIATED;
                    logs->push_back(new ErrorLogger(resultCode));
                }
                break;
            case ADDITION_OPERATION:
                this->value = childrenList[0]->value + childrenList[1]->value;
                break;
            case SUBSTRACTION_OPERATION:
                this->value = childrenList[0]->value - childrenList[1]->value;
                break;
            case MULTIPLICATION_OPERATION:
                this->value = childrenList[0]->value * childrenList[1]->value;
                break;
            case DIVISION_OPERATION:
                if (childrenList[1]->value == 0) {
                    resultCode = DIVISION_BY_ZERO;
                    logs->push_back(new ErrorLogger(resultCode));
                } else {
                    this->value = childrenList[0]->value / childrenList[1]->value;
                }
                break;
            case SINE_OPERATION:
                this->value = sin(this->childrenList[0]->value);
                break;
            case COSINE_OPERATION:
                this->value = cos(this->childrenList[0]->value);
                break;
            default:
                resultCode = NODE_OF_WRONG_TYPE;
                logs->push_back(new ErrorLogger(resultCode));
                break;
        }
    }
    if (resultCode == SUCCESS_CODE) {
        this->valueComputed = true;
    }
    return resultCode;
}

double Node::getValue() {
    return value;
}

int Node::setValueForVariable(int value) {
    if (this->nodeType == VARIABLE) {
        this->value = value;
        this->valueComputed = true;
        return SUCCESS_CODE;
    } else {
        return NODE_OF_WRONG_TYPE;
    }
}

string Node::getVariableName() {
    return this->variableName;
}

string Node::toString() {
    stringstream stream;
    switch (this->nodeType) {
        case VALUE:
            stream << this->value;
            break;
        case VARIABLE:
            stream << this->variableName;
            break;
        case ADDITION_OPERATION:
            stream << PLUS_SIGN;
            break;
        case SUBSTRACTION_OPERATION:
            stream << MINUS_SIGN;
            break;
        case MULTIPLICATION_OPERATION:
            stream << MULTIPLICATION_SIGN;
            break;
        case DIVISION_OPERATION:
            stream << DIVISION_SIGN;
            break;
        case SINE_OPERATION:
            stream << SINE_SIGN;
            break;
        case COSINE_OPERATION:
            stream << COSINE_SIGN;
            break;
        default:
            break;
    }
    for (int i = 0; i < getNumberOfChildren(); ++i) {
        stream << SPACE << childrenList[i]->toString();
    }
    stream << SPACE;
    return stream.str();
}

string Node::getArgumentFromInputLine(const string &inputLine, unsigned long &currentPosition) {
    unsigned long length = inputLine.length();
    if (currentPosition >= length) {
        return "";
    }
    unsigned long beginOfArgument = inputLine.find_first_not_of(SPACE, currentPosition);
    if (beginOfArgument >= length) {
        return "";
    }
    unsigned long endOfArgument = inputLine.find_first_of(SPACE, beginOfArgument);
    if (endOfArgument > length) {
        currentPosition = length;
    } else {
        currentPosition = endOfArgument;
    }
    return inputLine.substr(beginOfArgument, currentPosition - beginOfArgument);
}

int Node::getNumberOfChildren() {
    return this->numberOfChildren;
}

Node::Node(vector<ErrorLogger *> *logs) {
    this->logs = logs;
}

Node::~Node() {
    for (int i = 0; i < numberOfChildren; ++i) {
        delete childrenList[i];
    }
    delete childrenList;
}
