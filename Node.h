//
// Created by krispy1396 on 12.11.2017.
//

#ifndef ZMPO_LISTA3_NODE_H
#define ZMPO_LISTA3_NODE_H

#include <sstream>
#include <regex>
#include <cmath>
#include <vector>
#include "NodeType.h"
#include "ErrorLogger.h"

using namespace std;

class Node {
private:
    NodeType nodeType;
    Node **childrenList;
    int numberOfChildren;
    vector<ErrorLogger *> *logs;

    double value;
    string variableName;
    bool valueComputed = false;

    int getNumberOfChildren();

    string getArgumentFromInputLine(const string &inputLine, unsigned long &currentPosition);

    int initializeChildren(const string &inputLine, unsigned long &currentPosition, vector<Node *> &variables);

public:
    explicit Node(vector<ErrorLogger *> *logs);

    ~Node();

    int initializeNode(const string &inputLine, unsigned long &currentPosition, vector<Node *> &variables);

    int computeValue();

    double getValue();

    int setValueForVariable(int value);

    string getVariableName();

    string toString();

};


#endif //ZMPO_LISTA3_NODE_H
