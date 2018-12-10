//
// Created by krispy1396 on 12.11.2017.
//

#ifndef ZMPO_LISTA3_TREE_H
#define ZMPO_LISTA3_TREE_H


#include "Node.h"
#include "ErrorLogger.h"
#include <vector>


class Tree {
private:
    Node *root;
    vector<Node *> variables;
    vector<ErrorLogger *> logs;
    vector<string> distinctVariables;

    void setDistinctVariables();

public:
    Tree();

    ~Tree();

    int initializeTreeWithFormula(string &inputString);

    int computeTreeValue();

    string getVariableNodesAsString();

    int setValuesForVariableNodes(string &lineWithValues);

    int joinTree(Tree &tree);

    string toString();

    double getValue();

    Tree &operator=(string stringOfTree);

    string &operator+(Tree &otherTree);

    string getAndClearLogs();
};


#endif //ZMPO_LISTA3_TREE_H
