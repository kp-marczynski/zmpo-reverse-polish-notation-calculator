//
// Created by krispy1396 on 12.11.2017.
//

#include "Interface.h"

const char *WRONG_COMMAND = "Nie rozpoznano wprowadzonej instrukcji\n";
const char SPACE = ' ';
const char *VARS_TEXT = "Zmienne: ";
const char *TREE_TEXT = "Formula zapisana w drzewie: ";
const char *TREE_VALUE = "Wartosc drzewa: ";
const char *TREE_READ = "Wczytano drzewo: ";

int main() {
    Interface::showInterface();
    return 0;
}

void Interface::showInterface() {
    Tree *tree = nullptr;
    bool endOfProgram = false;
    cout << HELLO_MESSAGE;

    while (!endOfProgram) {
        cout << OPERATION_PROMPT;
        string lineFromUser;
        getline(cin, lineFromUser);

        string command;
        unsigned long beginOfCommand = lineFromUser.find_first_not_of(SPACE);
        if (beginOfCommand > lineFromUser.length()) {
            command = "";
        } else {
            unsigned long endOfCommand = lineFromUser.find_first_of(SPACE, beginOfCommand);
            if (endOfCommand > lineFromUser.length()) {
                endOfCommand = lineFromUser.length();
            }
            unsigned long length = endOfCommand - beginOfCommand;
            command = lineFromUser.substr(beginOfCommand, length);
            lineFromUser = lineFromUser.substr(endOfCommand);
        }

        if (command == ENTER_INSTRUCTION) {
            if (tree != nullptr) {
                delete tree;
            }
            tree = new Tree();
            tree->initializeTreeWithFormula(lineFromUser);
            cout << TREE_READ << tree->toString();
        } else if (command == VARS_INSTRUCTION) {
            cout << VARS_TEXT << tree->getVariableNodesAsString();
        } else if (command == PRINT_INSTRUCTION) {
            cout << TREE_TEXT << tree->toString();
        } else if (command == COMP_INSTRUCTION) {
            if (tree->setValuesForVariableNodes(lineFromUser) == SUCCESS_CODE) {
                if (tree->computeTreeValue() == SUCCESS_CODE) {
                    cout << TREE_VALUE << tree->getValue();
                }
            }
        } else if (command == JOIN_INSTRUCTION) {
            Tree tree2;
            if (tree2.initializeTreeWithFormula(lineFromUser) == SUCCESS_CODE) {
                *tree = *tree + tree2;
                cout << TREE_READ << tree->toString();
            }
        } else if (command == END_INSTRUCTION) {
            endOfProgram = true;
        } else {
            cerr << WRONG_COMMAND;
        }
        cerr << tree->getAndClearLogs();
    }
}
