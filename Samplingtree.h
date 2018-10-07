//
// Created by jamal on 30/09/2018.
//

#include "SamplingTreeNode.h"
#include <string>
using namespace std;

#ifndef MARKOVDECISION_SAMPLINGTREE_H
#define MARKOVDECISION_SAMPLINGTREE_H


class Samplingtree {
private:
    int numProbs;
    SamplingTreeNode** probs;
    SamplingTreeNode* root;
    void makeTree();
    void traversePostOrderHelper(SamplingTreeNode* node);
public:
    Samplingtree(int n, float* inprobs);
    void traversePostOrder();
};


#endif //MARKOVDECISION_SAMPLINGTREE_H
