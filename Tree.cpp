//
// Created by krispy1396 on 12.11.2017.
//

#include "Tree.h"

const char *REGEX_TEMPLATE = "^-?\\d+";
const char *COMA = ", ";
const char *SPACE_SIGN = " ";

Tree::Tree() {
    this->root = new Node(&logs);
}

Tree::~Tree() {
    delete root;
    variables.clear();
    logs.clear();
}

int Tree::computeTreeValue() {
    return root->computeValue();
}

double Tree::getValue() {
    return root->getValue();
}

int Tree::initializeTreeWithFormula(string &inputString) {
    unsigned long currentPosition = 0;
    int resultCode = root->initializeNode(inputString, currentPosition, variables);
    if (currentPosition < inputString.length()) {
        unsigned long index = inputString.find_first_not_of(SPACE_SIGN, currentPosition);
        if (index < inputString.length()) {
            logs.push_back(new ErrorLogger(ARGUMENTS_LEFT));
        }
    }
    setDistinctVariables();
    return resultCode;
}

string Tree::getVariableNodesAsString() {
    setDistinctVariables();
    stringstream stream;
    for (int i = 0; i < distinctVariables.size(); ++i) {
        stream << distinctVariables.at(i);
        if (i < distinctVariables.size() - 1) {
            stream << COMA;
        }
    }
    return stream.str();
}

int Tree::setValuesForVariableNodes(string &lineWithValues) {
    setDistinctVariables();
    int resultCode = SUCCESS_CODE;
    stringstream stream(lineWithValues);
    string argument;
    for (int i = 0; i < distinctVariables.size() && resultCode == SUCCESS_CODE; ++i) {

        stream >> argument;
        regex regexIsNumber(REGEX_TEMPLATE);
        bool isNumber = regex_match(argument, regexIsNumber);
        if (isNumber) {
            for (int j = 0; j < variables.size(); ++j) {
                if (variables[j]->getVariableName() == distinctVariables[i]) {
                    variables.at(j)->setValueForVariable(stoi(argument));
                }
            }
        } else {
            resultCode = ARGUMENT_IS_NOT_NUMBER;
            logs.push_back(new ErrorLogger(resultCode));
        }
    }
    return resultCode;
}

string Tree::toString() {
    return root->toString();
}

string &Tree::operator+(Tree &otherTree) {
    string tree1String = this->toString();
    string tree2String = otherTree.toString();


    bool leafRemoved = false;
    while (!leafRemoved) {
        string tempString = tree1String.substr(0, tree1String.find_last_of(SPACE_SIGN, tree1String.length()));
        if (tempString.length() < tree1String.length() - 1) {
            leafRemoved = true;
        }
        tree1String = tempString;
    }
//    Tree* tree = new Tree();
//    tree->initializeTreeWithFormula(tree1String+tree2String);

    return tree1String.append(SPACE_SIGN).append(tree2String);
}

Tree &Tree::operator=(string stringOfTree) {
    delete root;
    variables.clear();
    this->root = new Node(&logs);
    unsigned long currentPosition = 0;
    this->root->initializeNode(stringOfTree, currentPosition, this->variables);
    return *this;
}

int Tree::joinTree(Tree &tree) {
    return 0;
}

string Tree::getAndClearLogs() {
    stringstream stream;
    for (int i = 0; i < logs.size(); ++i) {
        stream << logs.at(i)->toString();
    }
    logs.clear();
    return stream.str();
}

void Tree::setDistinctVariables() {
    for (int i = 0; i < variables.size(); ++i) {
        bool variableFound = false;
        for (int j = 0; j < distinctVariables.size() && !variableFound; ++j) {
            if (distinctVariables[j] == variables[i]->getVariableName()) {
                variableFound = true;
            }
        }
        if (!variableFound) {
            distinctVariables.push_back(variables[i]->getVariableName());
        }
    }
}
