//
// Created by jamal on 30/09/2018.
//

#include <math.h>
#include "Samplingtree.h"

Samplingtree::Samplingtree(int n, float* inprobs) {
    numProbs = n;
    probs = new SamplingTreeNode*[10];
    for (int i = 0; i < n; i++) {
        probs[i]->setProbability(inprobs[i]);
    }
    makeTree(inprobs);
}

void Samplingtree::makeTree(float* inprobs) {
    SamplingTreeNode** currentlayer = probs;
    SamplingTreeNode** nextlayer = nullptr;
    for (int i = log2(numProbs); i > 0; i--) {
        nextlayer = new SamplingTreeNode*[pow(2, i-1)];
        for (int j = 0; j < (pow(2, i)); j++) {
            auto* newNode = new SamplingTreeNode;
            newNode->setLeftChild(currentlayer[j]);
            newNode->setRightChild(currentlayer[j+1]);
            newNode->setProbability(currentlayer[j]->getProbability() + currentlayer[j+1]->getProbability());
            currentlayer[j]->setParent(newNode);
            currentlayer[j+1]->setParent(newNode);
            nextlayer[j/2] = newNode;
            j++;
        }
        if (i != log2(numProbs)) {
            delete [] currentlayer;
        }
        currentlayer = nextlayer;
        if (i==1) {
            root = nextlayer[0];
        }
        delete [] nextlayer;
    }
}
