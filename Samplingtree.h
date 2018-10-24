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
    int numOrgProbs;
    SamplingTreeNode** probs;
    SamplingTreeNode* root;
    void makeTree();
    void traversePostOrderHelper(SamplingTreeNode* node);
    void deleteTreeHelper(SamplingTreeNode* node);
    void updateHelper(SamplingTreeNode* node);
public:
    Samplingtree(int n, double* inprobs);
    void updateProb(double * newprob);
    void updateProb(int index, double newprob);
    void traversePostOrder();
    void deleteTree();
    int performSampling();
};


#endif //MARKOVDECISION_SAMPLINGTREE_H
