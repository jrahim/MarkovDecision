//
// Created by jamal on 30/09/2018.
//
#include "SamplingTreeNode.cpp"

#ifndef MARKOVDECISION_SAMPLINGTREE_H
#define MARKOVDECISION_SAMPLINGTREE_H


class Samplingtree {
private:
    int numProbs;
    SamplingTreeNode* probs;
public:
    Samplingtree(int n);
};


#endif //MARKOVDECISION_SAMPLINGTREE_H
