//
// Created by jamal on 30/09/2018.
//

#include "SamplingTreeNode.cpp"

#ifndef MARKOVDECISION_SAMPLINGTREE_H
#define MARKOVDECISION_SAMPLINGTREE_H


class Samplingtree {
private:
    int numProbs;
    SamplingTreeNode** probs;
    void makeTree(float* inprobs);
public:
    Samplingtree(int n, float* inprobs);
};


#endif //MARKOVDECISION_SAMPLINGTREE_H
