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
}

void Samplingtree::makeTree(float* inprobs) {
    SamplingTreeNode** currentlayer = probs;
    SamplingTreeNode** nextlayer = nullptr;
    for (int i = log2(numProbs); i >= 0; i--) {
        nextlayer = ( (i >= 0) ? new SamplingTreeNode[pow(2, i-1)] : nullptr );
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
        curren
    }
}
